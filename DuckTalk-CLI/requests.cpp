#include <iostream>
#include <string>
#include <vector>
#include <boost/asio.hpp>

#include "requests.hpp"

using boost::asio::ip::tcp;

    HttpRequests::HttpRequests(std::string ip, std::string host_port) {
        host = ip;
        port = host_port;
    }

    std::string HttpRequests::get_request(std::string path) {
        boost::asio::io_service io_service;
        // Resolve DNS to get the IP address of the server
        try {
            tcp::resolver resolver(io_service);
            tcp::resolver::query query(host, port);
            tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

            // Establish a connection to the server
            tcp::socket socket(io_service);
            boost::asio::connect(socket, endpoint_iterator);

            // Send the HTTP request
            boost::asio::streambuf request;
            std::ostream request_stream(&request);
            request_stream << "GET " << path << " HTTP/1.1\r\n";
            request_stream << "Host: " << host << "\r\n";
            request_stream << "Accept: */*\r\n";
            request_stream << "Connection: close\r\n\r\n";

            boost::asio::write(socket, request);

            // Read the response
            boost::asio::streambuf response;
            boost::asio::read_until(socket, response, "\r\n\r\n");

            // Discard the headers from the response stream
            std::istream response_stream(&response);
            std::string header;
            while (std::getline(response_stream, header) && header != "\r");

            // Read the body of the response
            std::stringstream ss;
            ss << &response;

            return ss.str();
        }
        catch (const std::exception& e) {
            std::stringstream ss;
            ss << "Error resolving hostname: " << e.what() << std::endl;
            return ss.str();
        }
    }



    std::string HttpRequests::post_request(const std::string& path, const std::string& payload) {
        boost::asio::io_service io_service;
        try {
            // Resolve DNS to get the IP address of the server
            tcp::resolver resolver(io_service);
            tcp::resolver::query query(host, port);
            tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

            // Establish a connection to the server
            tcp::socket socket(io_service);
            boost::asio::connect(socket, endpoint_iterator);

            // Build the HTTP request
            std::stringstream request_stream;
            request_stream << "POST " << path << " HTTP/1.1\r\n";
            request_stream << "Host: " << host << "\r\n";
            request_stream << "Content-Type: application/json\r\n";
            request_stream << "Content-Length: " << payload.length() << "\r\n";
            request_stream << "Connection: close\r\n\r\n";
            request_stream << payload;

            // Send the HTTP request
            boost::asio::streambuf request;
            std::ostream request_buf(&request);
            request_buf << request_stream.str();
            boost::asio::write(socket, request);

            // Read the response
            boost::asio::streambuf response;
            boost::asio::read_until(socket, response, "\r\n");

            // Discard the headers from the response stream
            std::istream response_stream(&response);
            std::string header;
            while (std::getline(response_stream, header) && header != "\r");

            // Read the body of the response
            std::stringstream ss;
            ss << &response;

            return ss.str();
        }
        catch (const std::exception& e) {
            std::stringstream ss;
            ss << "Error resolving hostname: " << e.what() << std::endl;
            return ss.str();
        }
    }

