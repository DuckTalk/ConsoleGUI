#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include "requests.hpp"



std::unordered_map<std::string, std::string> read_config_file(const std::string& file_path)
{
    std::ifstream file(file_path);
    std::unordered_map<std::string, std::string> config;

    if (!file.good()) {
        std::ofstream default_config(file_path);
        default_config << "api_host=" << std::endl;
        default_config.close();
        std::cerr << "No config file found, created a default one with empty api_host" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            config[key] = value;
        }
    }

    file.close();

    if (config.empty()) {
        std::cerr << "The config file is empty or invalid" << std::endl;
        exit(EXIT_FAILURE);
    }

    return config;
}


void handle_command(const std::string host, const std::string& cmd, const std::string& arg1, const std::string& arg2 = "", const std::string& arg3 = "")
{
    if (cmd == "login" && arg2 != "" && arg3 != "") {
        std::cout << "Loging in as  " << arg1 << "With the email: " << arg2 << std::endl;
        // Implement logic to login the user
    }

    if (cmd == "send_message") {
        std::cout << "Sending message " << arg1 << std::endl;
        // implement logic to send post

        // Define the API endpoint
        std::string endpoint = "/posts";

        // Define the request payload
        std::string payload = R"(
            {
                "title": "foo",
                "body": "bar",
                "userId": 1
            }
        )";

        // Make the HTTP POST request
        HttpRequests request("jsonplaceholder.typicode.com");
        std::string response = request.post_request(endpoint, payload);

        // Print the response
        std::cout << response << std::endl;

    }

    if (cmd == "get_messages") {
        std::cout << "Getting messages " << arg1 << std::endl;
        HttpRequests request(host);
        std::string response = request.get_request();
        std::cout << response << std::endl;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " [command]" << std::endl;
        return 1;
    }

    std::string config_path = "config.ini";
    std::unordered_map<std::string, std::string> config = read_config_file(config_path);
    std::string api_host = config["api_host"];

    // Handle the command
    std::string cmd = argv[1];
    std::string arg1 = argv[2];
    std::string arg2 = argc > 3 ? argv[3] : "";
    std::string arg3 = argc > 4 ? argv[4] : "";

    handle_command(api_host, cmd, arg1, arg2, arg3);

    return 0;
}