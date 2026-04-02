#include "WSClient.h"
#include <iostream>

WSClient::WSClient() {}

WSClient::~WSClient() {
    close();
}

bool WSClient::connectUrl(const std::string& url) {
    std::string host, path = "/";

    size_t pos = url.find("://");
    size_t start = (pos == std::string::npos) ? 0 : pos + 3;
    size_t slash = url.find('/', start);

    if (slash == std::string::npos) {
        host = url.substr(start);
    }
    else {
        host = url.substr(start, slash - start);
        path = url.substr(slash);
    }

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

    hConnect = WinHttpConnect(hSession, host.c_str(),
        INTERNET_DEFAULT_HTTPS_PORT, 0);

    if (!hConnect) return false;

    hRequest = WinHttpOpenRequest(
        hConnect,
        L"GET",
        path.c_str(),
        NULL,
        WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES,
        WINHTTP_FLAG_SECURE
    );

    if (!hRequest) return false;

    WinHttpSetOption(hRequest,
        WINHTTP_OPTION_UPGRADE_TO_WEB_SOCKET,
        NULL, 0);

    if (!WinHttpSendRequest(hRequest,
        WINHTTP_NO_ADDITIONAL_HEADERS, 0,
        WINHTTP_NO_REQUEST_DATA, 0,
        0, 0)) return false;

    if (!WinHttpReceiveResponse(hRequest, NULL)) return false;

    hWebSocket = WinHttpWebSocketCompleteUpgrade(hRequest, 0);
    if (!hWebSocket) return false;

    connected = true;
    running = true;

    recvThread = std::thread(&WSClient::receiveLoop, this);

    std::cout << "WebSocket Connected\n";
    return true;
}

void WSClient::receiveLoop() {
    char buffer[1024];

    while (running) {
        DWORD bytesRead = 0;
        WINHTTP_WEB_SOCKET_BUFFER_TYPE type;

        HRESULT hr = WinHttpWebSocketReceive(
            hWebSocket,
            buffer,
            sizeof(buffer),
            &bytesRead,
            &type
        );

        if (FAILED(hr)) {
            std::cout << "Receive error\n";
            break;
        }

        if (type == WINHTTP_WEB_SOCKET_CLOSE_BUFFER_TYPE) {
            std::cout << "Server closed\n";
            break;
        }

        if (bytesRead > 0) {
            std::lock_guard<std::mutex> lock(queueMutex);
            messageQueue.push(std::string(buffer, bytesRead));
        }
    }

    connected = false;
    running = false;
}

void WSClient::send(const std::string& msg) {
    if (!connected) return;

    std::lock_guard<std::mutex> lock(sendMutex);

    WinHttpWebSocketSend(
        hWebSocket,
        WINHTTP_WEB_SOCKET_UTF8_MESSAGE_BUFFER_TYPE,
        (PVOID)msg.c_str(),
        msg.size()
    );
}

bool WSClient::pollMessage(std::string& out) {
    std::lock_guard<std::mutex> lock(queueMutex);

    if (messageQueue.empty()) return false;

    out = messageQueue.front();
    messageQueue.pop();
    return true;
}

void WSClient::close() {
    running = false;

    if (hWebSocket) {
        WinHttpWebSocketClose(hWebSocket, 1000, NULL, 0);
        WinHttpCloseHandle(hWebSocket);
        hWebSocket = nullptr;
    }

    if (recvThread.joinable()) {
        recvThread.join();
    }

    cleanup();
    connected = false;
}

bool WSClient::isConnected() const {
    return connected.load();
}

void WSClient::cleanup() {
    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hSession) WinHttpCloseHandle(hSession);

    hRequest = nullptr;
    hConnect = nullptr;
    hSession = nullptr;
}