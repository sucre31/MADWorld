#pragma once
#include <windows.h>
#include <winhttp.h>
#include <string>
#include <thread>
#include <atomic>
#include <mutex>
#include <queue>
#include <functional>

#pragma comment(lib, "winhttp.lib")

class WSClient {
public:
    WSClient();
    ~WSClient();

    bool connectUrl(const std::string& url);
    bool connect(const std::wstring& host, const std::wstring& path);

    void send(const std::string& msg);
    void close();

    bool isConnected() const;

    bool pollMessage(std::string& out); // 既存のポーリングも残す

    // 新規: メッセージ変化コールバック登録
    void setOnMessageChanged(std::function<void(const std::string&)> cb);

private:
    void receiveLoop();
    void cleanup();

    // WinHTTP
    HINTERNET hSession = nullptr;
    HINTERNET hConnect = nullptr;
    HINTERNET hRequest = nullptr;
    HINTERNET hWebSocket = nullptr;

    // スレッド
    std::thread recvThread;
    std::atomic<bool> running{ false };
    std::atomic<bool> connected{ false };

    // 送信保護
    std::mutex sendMutex;

    // 受信メッセージ
    std::queue<std::string> messageQueue;
    std::mutex queueMutex;

    // 前回値保存
    std::string lastMessage;

    // コールバック
    std::function<void(const std::string&)> onMessageChanged;
};