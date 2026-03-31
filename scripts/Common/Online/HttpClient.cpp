#include "HttpClient.h"

HttpClient::HttpClient() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

HttpClient::~HttpClient() {
    curl_global_cleanup();
}

// GET
std::string HttpClient::get(const std::string& url) {
    return request(url, "GET", "");
}

// POST
std::string HttpClient::post(const std::string& url, const std::string& body) {
    return request(url, "POST", body);
}


size_t HttpClient::writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    std::string* str = static_cast<std::string*>(userp);
    str->append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

std::string HttpClient::request(const std::string& url, const std::string& method, const std::string& body) {
    CURL* curl = curl_easy_init();
    std::string response;

    if (!curl) return "";

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // タイムアウト（重要）
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3L);

    if (method == "POST") {
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    }

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        response = ""; // エラー時は空
    }

    curl_easy_cleanup(curl);
    return response;
}