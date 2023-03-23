#include <iostream>
#include <string>
#include <vector>

void handle_command(const std::string& cmd, const std::string& arg1)
{
    if (cmd == "send") {
        std::cout << "Sending: " << arg1 << std::endl;
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
