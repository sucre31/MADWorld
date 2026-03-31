#pragma once
#include <string>
#include <curl/curl.h>

class HttpClient
{
public:
    HttpClient();
    ~HttpClient();
    std::string get(const std::string& url);
    std::string post(const std::string& url, const std::string& body);

private:
    static size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp);

    std::string request(const std::string& url, const std::string& method, const std::string& body);
};