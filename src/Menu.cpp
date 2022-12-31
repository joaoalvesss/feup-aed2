#include "../headers/Menu.h"
#include <iostream>

bool Menu::exitApplication = false;

void Menu::init() {
    Manager manager = Manager();

    while (!Menu::exitApplication) {
        int option = Menu::showMainMenu();

        switch (option) {
            case QUIT_AND_SAVE:
                break;
            case MAKE_A_REQUEST:
                break;
            case DISPLAY_INFORMATION:
                break;
            case MIN_PATH_TEST:
                Menu::travelMinAirports(manager);
                break;
        }
    }
}

void Menu::wait(const std::string &string) {
    std::cout << string << std::endl;
    std::cin.get();
    if (std::cin.peek() == '\n') std::cin.ignore(50, '\n'); // we don't expect the input to be more than 50 characters
}

int Menu::showMainMenu() {
    int choice;

    std::cout << std::endl;
    std::cout << "------- Main Menu -------" << std::endl;
    std::cout << "[1] Quit and Save" << std::endl;
    std::cout << "[2] Make a request" << std::endl;
    std::cout << "[3] Display information" << std::endl;
    std::cout << "[4] Display information" << std::endl;

    std::cout << "Enter your choice: ";
    std::cin >> choice;

    if (!std::cin)
        exit(0);

    std::cout.flush();

    return choice;
}

void Menu::travelMinAirports(Manager& manager) {
    manager.printMinPath();
    Menu::wait("\n\t[press ENTER to continue]");
}