#include <iostream>
#include <string>
#include <vector>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

void get_request() {
    boost::asio::io_service io_service;

    // Resolve DNS to get the IP address of the server
    tcp::resolver resolver(io_service);
    tcp::resolver::query query("example.com", "80");
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    // Establish a connection to the server
    tcp::socket socket(io_service);
    boost::asio::connect(socket, endpoint_iterator);

    // Send the HTTP request
    boost::asio::streambuf request;
    std::ostream request_stream(&request);
    request_stream << "GET / HTTP/1.1\r\n";
    request_stream << "Host: example.com\r\n";
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
    std::cout << "Response: " << http_version << " " << status_code << " " << status_message << std::endl;

    // Print the response headers
    boost::asio::read_until(socket, response, "\r\n\r\n");
    std::string header;
    while (std::getline(response_stream, header) && header != "\r")
    {
        std::cout << header << std::endl;
    }
    std::cout << std::endl;

    // Print the response body
    if (response.size() > 0)
    {
        std::cout << boost::asio::buffer_cast<const char*>(response.data()) << std::endl;
    }
}

void handle_command(const std::string& cmd, const std::string& arg1)
{
    if (cmd == "send") {
        // implement logic to send post
        std::cout << "Sending post " << arg1 << std::endl;
    }

    if (cmd == "get") {
        get_request();
        std::cout << "Sending get " << arg1 << std::endl;
    }
}

int main(int argc, char* argv[])
{
    get_request();
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " [command]" << std::endl;
        return 1;
    }

    std::string cmd = argv[1];
    std::string arg1 = argv[2];

    handle_command(cmd, arg1);

    return 0;
}
