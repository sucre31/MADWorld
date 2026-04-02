//#pragma once
//#include <string>
//#include <thread>
//#include <queue>
//#include <mutex>
//#include <functional>
//#include <condition_variable>
//
//class HttpClient {
//public:
//    HttpClient();
//    ~HttpClient();
//
//    void getAsync(const std::string& url, std::function<void(std::string)> callback);
//    void putAsync(const std::string& url, const std::string& body,
//        std::function<void(std::string)> callback);
//
//    void update(); // メインスレッドで呼ぶ
//
//private:
//    static size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp);
//
//    struct Request {
//        std::string url;
//        std::string method;
//        std::string body;
//        std::function<void(std::string)> callback;
//    };
//
//    std::queue<Request> requestQueue;
//    std::queue<std::pair<std::function<void(std::string)>, std::string>> resultQueue;
//
//    std::mutex mutex;
//    std::condition_variable cv;
//
//    std::thread worker;
//    bool running = true;
//
//    void threadFunc();
//    std::string request(const std::string& url,
//        const std::string& method,
//        const std::string& body);
//};