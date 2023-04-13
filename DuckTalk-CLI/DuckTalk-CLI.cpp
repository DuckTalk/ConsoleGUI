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


void handle_command(const std::string host, const std::string& cmd, const std::string& arg1)
{
    if (cmd == "send") {
        // implement logic to send post
        std::cout << "Sending post " << arg1 << std::endl;
    }

    if (cmd == "get") {
        HttpRequests request(host);
        std::string response = request.get_request();
        std::cout << response << std::endl;
        std::cout << "Sending get " << arg1 << std::endl;
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

    handle_command(api_host, cmd, arg1);

    return 0;
}