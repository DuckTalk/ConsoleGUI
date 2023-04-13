#include <iostream>
#include <string>
#include <vector>
#include <boost/asio.hpp>

#include "requests.hpp"

using boost::asio::ip::tcp;

    HttpRequests::HttpRequests(std::string ip) {
        host = ip;
    }

    std::string HttpRequests::get_request() {
        boost::asio::io_service io_service;

        // Resolve DNS to get the IP address of the server
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(host, "80");
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        // Establish a connection to the server
        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);

        // Send the HTTP request
        boost::asio::streambuf request;
        std::ostream request_stream(&request);
        request_stream << "GET / HTTP/1.1\r\n";
        request_stream << "Host: " << host << "\r\n";
        request_stream << "Accept: */*\r\n";
        request_stream << "Connection: close\r\n\r\n";

        boost::asio::write(socket, request);

        // Read the response
        boost::asio::streambuf response;
        boost::asio::read_until(socket, response, "\r\n");

        // Print the response
        std::istream response_stream(&response);
        std::string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        std::string status_message;
        std::getline(response_stream, status_message);

        std::stringstream ss;
        ss << "Response: " << http_version << " " << status_code << " " << status_message << std::endl;

        // Read the rest of the response
        if (response.size() > 0) {
            ss << &response;
        }

        return ss.str();
    }
