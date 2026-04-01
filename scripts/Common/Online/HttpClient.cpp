#include "HttpClient.h"
#include <curl/curl.h>

size_t HttpClient::writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    std::string* str = static_cast<std::string*>(userp);
    str->append((char*)contents, size * nmemb);
    return size * nmemb;
}

HttpClient::HttpClient() {
    curl_global_init(CURL_GLOBAL_DEFAULT);

    worker = std::thread(&HttpClient::threadFunc, this);
}

HttpClient::~HttpClient() {
    running = false;
    cv.notify_all();
    if (worker.joinable()) worker.join();

    curl_global_cleanup();
}

void HttpClient::getAsync(const std::string& url, std::function<void(std::string)> callback) {
    std::lock_guard<std::mutex> lock(mutex);
    requestQueue.push({ url, callback });
    cv.notify_one();
}

void HttpClient::update() {
    std::lock_guard<std::mutex> lock(mutex);

    while (!resultQueue.empty()) {
        auto& [callback, result] = resultQueue.front();
        callback(result); // ← メインスレッドで実行
        resultQueue.pop();
    }
}

void HttpClient::threadFunc() {
    while (running) {
        Request req;

        {
            std::unique_lock<std::mutex> lock(mutex);
            cv.wait(lock, [&]() { return !requestQueue.empty() || !running; });

            if (!running) return;

            req = requestQueue.front();
            requestQueue.pop();
        }

        std::string res = request(req.url);

        {
            std::lock_guard<std::mutex> lock(mutex);
            resultQueue.push({ req.callback, res });
        }
    }
}

std::string HttpClient::request(const std::string& url) {
    CURL* curl = curl_easy_init();
    std::string response;

    if (!curl) return "";

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3L);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    return response;
}