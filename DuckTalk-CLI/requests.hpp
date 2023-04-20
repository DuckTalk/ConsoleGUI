#pragma once
#ifndef HTTP_REQUESTS_HPP
#define HTTP_REQUESTS_HPP

#include <string>

class HttpRequests {
public:
    HttpRequests(std::string ip);
    std::string get_request();
    std::string post_request(const std::string& path, const std::string& payload);
protected:
    std::string host;
};

#endif
