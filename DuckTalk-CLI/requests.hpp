#pragma once
#ifndef GET_REQUEST_HPP
#define GET_REQUEST_HPP

#include <string>

class HttpRequests {
public:
    HttpRequests(std::string host);
    std::string get_request();
protected:
    std::string host;
};

#endif
