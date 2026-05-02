#include "WSClient.h"
#include <iostream>

#ifndef WINHTTP_WEB_SOCKET_UTF8_FRAGMENT_MESSAGE
typedef enum _WINHTTP_WEB_SOCKET_BUFFER_TYPE_FIX {
    WINHTTP_WEB_SOCKET_BINARY_MESSAGE = 0,
    WINHTTP_WEB_SOCKET_BINARY_FRAGMENT_MESSAGE = 1,
    WINHTTP_WEB_SOCKET_UTF8_MESSAGE = 2,
    WINHTTP_WEB_SOCKET_UTF8_FRAGMENT_MESSAGE = 3,
    WINHTTP_WEB_SOCKET_CLOSE_MESSAGE = 4
} WINHTTP_WEB_SOCKET_BUFFER_TYPE_FIX;
#endif

WSClient::WSClient() {}
WSClient::~WSClient() { close(); }

/*
@brief コールバック設定(Dxlib関数はスレッドセーフでないのでここでは登録しない)
*/
void WSClient::setOnMessageChanged(std::function<void(const std::string&)> cb) {
    onMessageChanged = cb;
}

bool WSClient::connectUrl(const std::string& url) {
    std::string host, path = "/";
    size_t pos = url.find("://");
    size_t start = (pos == std::string::npos) ? 0 : pos + 3;
    size_t slash = url.find('/', start);

    if (slash == std::string::npos) host = url.substr(start);
    else { host = url.substr(start, slash - start); path = url.substr(slash); }

    std::wstring whost(host.begin(), host.end());
    std::wstring wpath(path.begin(), path.end());
    return connect(whost, wpath);
}

bool WSClient::connect(const std::wstring& host, const std::wstring& path) {
    cleanup();

    hSession = WinHttpOpen(L"MyApp",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS, 0);
    if (!hSession) return false;

    hConnect = WinHttpConnect(hSession, host.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
    if (!hConnect) return false;

    hRequest = WinHttpOpenRequest(hConnect, L"GET", path.c_str(), NULL,
        WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
    if (!hRequest) return false;

    WinHttpSetOption(hRequest, WINHTTP_OPTION_UPGRADE_TO_WEB_SOCKET, NULL, 0);

    if (!WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0,
        WINHTTP_NO_REQUEST_DATA, 0, 0, 0)) return false;

    if (!WinHttpReceiveResponse(hRequest, NULL)) return false;

    hWebSocket = WinHttpWebSocketCompleteUpgrade(hRequest, 0);
    if (!hWebSocket) return false;

    connected = true;
    running = true;
    recvThread = std::thread(&WSClient::receiveLoop, this);

    std::cout << "WebSocket Connected\n";
    return true;
}

// WSClient.cpp 内の受信ループのイメージ修正
void WSClient::receiveLoop() {
    std::vector<char> messageBuffer; // データを蓄積するための動的バッファ
    const DWORD tempBufferSize = 4096;
    std::vector<char> tempBuffer(tempBufferSize);

    while (running) {
        DWORD bytesRead = 0;
        WINHTTP_WEB_SOCKET_BUFFER_TYPE bufferType;

        // 受信
        DWORD dwError = WinHttpWebSocketReceive(
            hWebSocket,
            tempBuffer.data(),
            (DWORD)tempBuffer.size(),
            &bytesRead,
            &bufferType
        );

        if (dwError != ERROR_SUCCESS) {
            connected = false;
            break;
        }

        // 読み取った分を蓄積バッファに追加
        messageBuffer.insert(messageBuffer.end(), tempBuffer.begin(), tempBuffer.begin() + bytesRead);

        // メッセージの終了判定
        if (bufferType == WINHTTP_WEB_SOCKET_UTF8_MESSAGE ||
            bufferType == WINHTTP_WEB_SOCKET_BINARY_MESSAGE) {

            // 完了メッセージ（フラグメントの最後、または一括受信）
            std::string fullMsg(messageBuffer.begin(), messageBuffer.end());

            {
                std::lock_guard<std::mutex> lock(queueMutex);
                messageQueue.push(fullMsg);
            }

            // 次のメッセージのためにバッファをクリア
            messageBuffer.clear();
        }
        else if (bufferType == WINHTTP_WEB_SOCKET_UTF8_FRAGMENT_MESSAGE ||
            bufferType == WINHTTP_WEB_SOCKET_BINARY_FRAGMENT_MESSAGE) {
            // まだ続きがある（フラグメント）
            // 何もしない（messageBufferに蓄積され、次のループで続きを読み込む）
            continue;
        }
        else if (bufferType == WINHTTP_WEB_SOCKET_CLOSE_MESSAGE) {
            connected = false;
            break;
        }
    }
}

void WSClient::send(const std::string& msg) {
    if (!connected) return;
    std::lock_guard<std::mutex> lock(sendMutex);

    WinHttpWebSocketSend(hWebSocket, WINHTTP_WEB_SOCKET_UTF8_MESSAGE_BUFFER_TYPE,
        (PVOID)msg.c_str(), msg.size());
}

bool WSClient::pollMessage(std::string& out) {
    std::lock_guard<std::mutex> lock(queueMutex);
    if (messageQueue.empty()) return false;

    out = messageQueue.front();
    messageQueue.pop();

    // onMessageChanged はメインスレッドで呼ぶ
    if (onMessageChanged) {
        onMessageChanged(out);
    }

    return true;
}

void WSClient::close() {
    running = false;

    if (hWebSocket) {
        WinHttpWebSocketClose(hWebSocket, 1000, NULL, 0);
        WinHttpCloseHandle(hWebSocket);
        hWebSocket = nullptr;
    }

    if (recvThread.joinable()) recvThread.join();

    cleanup();
    connected = false;
}

bool WSClient::isConnected() const { return connected.load(); }

void WSClient::cleanup() {
    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hSession) WinHttpCloseHandle(hSession);

    hRequest = nullptr;
    hConnect = nullptr;
    hSession = nullptr;
}