// DuckTalk.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <iostream>
#include <conio.h>

void displayChatInterface() {
    // Clear the console
    system("cls");

    // Initialize variables for field selection
    const int NUM_USER_CHANNELS = 3;
    const int NUM_GROUP_CHANNELS = 3;
    int selectedChannelIndex = 0;
    bool isUserChannelSelected = true;

    while (true) {
        // Print the interface
        std::cout << " ___________________________________________________________________________________________________" << std::endl;
        std::cout << "|              |                                                                                    |" << std::endl;
        std::cout << "|  DuckTalk    |                                                                                    |" << std::endl;
        std::cout << "|______________|                                                                                    |" << std::endl;
        std::cout << "|              |                                                                                    |" << std::endl;
        std::cout << "|  DMs         |                                                                                    |" << std::endl;
        std::cout << "|______________|                          Text  History                                             |" << std::endl;

        // Print the user channels and highlight the selected channel
        std::cout << "|              |                                                                                    |" << std::endl;
        std::cout << "|  ";
        if (isUserChannelSelected) {
            std::cout << "* ";
        }
        std::cout << "User 1";
        if (selectedChannelIndex == 0) {
            std::cout << " <=";
        }
        std::cout << "                                                                              |" << std::endl;
        std::cout << "|  ";
        if (isUserChannelSelected) {
            std::cout << "* ";
        }
        std::cout << "User 2";
        if (selectedChannelIndex == 1) {
            std::cout << " <=";
        }
        std::cout << "                                                                              |" << std::endl;
        std::cout << "|  ";
        if (isUserChannelSelected) {
            std::cout << "* ";
        }
        std::cout << "User 3";
        if (selectedChannelIndex == 2) {
            std::cout << " <=";
        }
        std::cout << "                                                                              |" << std::endl;

        // Print the group channels and highlight the selected channel
        std::cout << "|______________|                                                                                    |" << std::endl;
        std::cout << "|              |                                                                                    |" << std::endl;
        std::cout << "|  ";
        if (!isUserChannelSelected) {
            std::cout << "* ";
        }
        std::cout << "Group 1";
        if (selectedChannelIndex == NUM_USER_CHANNELS) {
            std::cout << " <=";
        }
        std::cout << "                                                                             |" << std::endl;
        std::cout << "|  ";
        if (!isUserChannelSelected) {
            std::cout << "* ";
        }
        std::cout << "Group 2";
        if (selectedChannelIndex == NUM_USER_CHANNELS + 1) {
            std::cout << " <=";
        }
        std::cout << "                                                                             |" << std::endl;
        std::cout << "|  ";
        if (!isUserChannelSelected) {
            std::cout << "* ";
        }
        std::cout << "Group 3";
        if (selectedChannelIndex == NUM_USER_CHANNELS + 2) {
            std::cout << " <=";
        }
        std::cout << "                                                                             |" << std::endl;
        std::cout << "|______________|____________________________________________________________________________________|" << std::endl;

        // Wait for user input
        // char input = _
    }
}

int main() {
    displayChatInterface();

    return 0;
}
