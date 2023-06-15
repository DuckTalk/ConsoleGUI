#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include "requests.hpp"
#include <nlohmann/json.hpp>



std::unordered_map<std::string, std::string> read_config_file(const std::string& file_path)
{
    std::ifstream file(file_path);
    std::unordered_map<std::string, std::string> config;

    if (!file.good()) {
        std::ofstream default_config(file_path);
        default_config << "host=" << std::endl;
        default_config << "port=" << std::endl;
        default_config.close();
        std::cerr << "No config file found, created a default config" << std::endl;
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


void handle_command(const std::string& host, const std::string& port, const std::string& cmd, const std::string& arg1 = "", const std::string& arg2 = "", const std::string& arg3 = "")
{
    if (cmd == "register") {
        // creates a user on the server
        try {
            std::string endpoint = "/api/user";
            nlohmann::json payload = {
                {"data", {
                    {"username", arg1},
                    {"email", arg2},
                    {"pw_hash", arg3},
                    {"salt", "beans"}
                }}
            };

            HttpRequests request(host, port);
            std::string response = request.post_request(endpoint, payload.dump());

            auto json_response = nlohmann::json::parse(response);
            if (json_response["error"] == false) {
                std::cout << "User created successfully" << std::endl;
            }
            else {
                std::cout << "An error occurred while creating the user" << std::endl;
            }
        }
        catch (const std::exception& e) {
            std::cout << "Error resolving hostname: " << e.what() << std::endl;
        }

    }
    else if (cmd == "login") {
        // this creates a pseudo login which saves the logged in userid into a text file
        int userid = NULL;
        std::string username = "";
        std::string userid_entpoint = "/api/user/" + arg1;

        HttpRequests request(host, port);
        std::string response_userid = request.get_request(userid_entpoint);

        auto userid_response = nlohmann::json::parse(response_userid);
        if (userid_response["error"] == false) {
            userid = userid_response["data"]["user_id"];
            username = userid_response["data"]["username"];

            // Save the user ID to a text file
            std::ofstream outfile("user_id.txt");
            outfile << userid;
            outfile.close();

            std::cout << "Successfully logged in as " << username << std::endl;
        }
        else {
            std::cout << "An error occurred while trying to get the user_id of email" << std::endl;
        }
    }
    else if (cmd == "send_message") {       
        try {
            int receiver_userid = NULL;
            int sender_userid = NULL;
            std::string endpoint = "/api/message";
            std::string userid_entpoint = "/api/user/" + arg2;


            HttpRequests request(host, port);
            std::string response_userid = request.get_request(userid_entpoint);

            auto userid_response = nlohmann::json::parse(response_userid);
            if (userid_response["error"] == false) {
                receiver_userid = userid_response["data"]["user_id"];
            }
            else {
                std::cout << "An error occurred while trying to get the user_id of email" << std::endl;
            }

            std::ifstream infile("user_id.txt");
            if (infile.is_open()) {
                infile >> sender_userid;
                infile.close();
            }
            else {
                std::cerr << "Failed to open user_id.txt" << std::endl;
            }


            nlohmann::json payload = {
                {"data", {
                    {"sender_id", sender_userid},
                    {"receiver", {
                        {"type", arg1},
                        {"user_id", receiver_userid}
                    }},
                    {"content", arg3}
                }}
            };

            std::string response = request.post_request(endpoint, payload.dump());

            auto json_response = nlohmann::json::parse(response);
            if (json_response["error"] == false) {
                std::cout << "Message sent successfully" << std::endl;
            }
            else {
                std::cout << "An error occurred while sending the message" << std::endl;
            }
        }
        catch (const std::exception& e) {
            std::cout << "Error resolving hostname: " << e.what() << std::endl;
        }

    }
    else {
        std::cout << "Invalid Command" << std::endl;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " [command]" << std::endl;
        return 1;
    }

    std::string config_path = "config.ini";
    std::unordered_map<std::string, std::string> config = read_config_file(config_path);
    std::string host = config["host"];
    std::string port = config["port"];

    const std::string prefix = "https://";
    if (host.compare(0, prefix.size(), prefix) == 0) {
        host = host.substr(prefix.size());
    }


    // Handle the command
    std::string cmd = argv[1];
    std::string arg1 = argc > 2 ? argv[2] : "";
    std::string arg2 = argc > 3 ? argv[3] : "";
    std::string arg3 = argc > 4 ? argv[4] : "";

    handle_command(host, port, cmd, arg1, arg2, arg3);

    return 0;
}