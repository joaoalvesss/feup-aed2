#include "../headers/Menu.h"
#include <iostream>

bool Menu::exitApplication = false;

void Menu::init() {
    Manager manager = Manager();

    while (!Menu::exitApplication) {
        int option = Menu::showMainMenu();

        switch (option) {
            case QUIT_AND_SAVE:
            case MAKE_A_REQUEST:
            case DISPLAY_INFORMATION:

                if (option == QUIT_AND_SAVE) {
                    // bla bla
                }

                else if (option == MAKE_A_REQUEST) {
                    // bla bla
                }

                else {
                    // bla bla
                }
        }
    }
}

int Menu::showMainMenu() {
    int choice;

    std::cout << std::endl;
    std::cout << "------- Main Menu -------" << std::endl;
    std::cout << "[1] Quit and Save" << std::endl;
    std::cout << "[2] Make a request" << std::endl;
    std::cout << "[3] Display information" << std::endl;

    std::cout << "Enter your choice: ";
    std::cin >> choice;

    if (!std::cin)
        exit(0);

    std::cout.flush();

    return choice;
}