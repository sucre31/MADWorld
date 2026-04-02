#pragma once
#include <windows.h>
#include <winhttp.h>
#include <string>
#include <thread>
#include <atomic>
#include <mutex>
#include <queue>

#pragma comment(lib, "winhttp.lib")

class WSClient {
public:
    WSClient();
    ~WSClient();

    // URLで接続（wss://〜）
    bool connectUrl(const std::string& url);

    // 分解版
    bool connect(const std::wstring& host, const std::wstring& path);

    void send(const std::string& msg);
    void close();

    bool isConnected() const;

    // ★ メインスレッドで呼ぶ
    bool pollMessage(std::string& out);

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

    // ★ 受信用キュー
    std::queue<std::string> messageQueue;
    std::mutex queueMutex;
};