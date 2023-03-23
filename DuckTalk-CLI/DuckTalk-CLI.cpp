#include <iostream>
#include <string>
#include <vector>
#include "lib/curl.h"
#include "lib/json.hpp"

using json = nlohmann::json;

void handle_command(const std::string& cmd, const std::string& arg1)
{
    if (cmd == "send") {
        std::cout << "Sending: " << arg1 << std::endl;

        std::string message = arg1;

        json data = {
            {"type", "message"},
            {"auth", {
                {"type", "token"},
                {"token", "token"}
            }},
            {"data", {
                {"receiver", {
                    {"type", "user"},
                    {"user_id", 92}
                }},
                {"content", message}
            }}
        };

        std::string data_str = data.dump();

        CURL* curl = curl_easy_init();

        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "http://ableytner.ddns.net:2006");

            curl_easy_setopt(curl, CURLOPT_POST, 1L);

            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data_str.c_str());

            CURLcode res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            }

            curl_easy_cleanup(curl);
        }


    }
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " [command]" << std::endl;
        return 1;
    }

    std::string cmd = argv[1];
    std::string arg1 = argv[2];

    handle_command(cmd, arg1);

    return 0;
}
