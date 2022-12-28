#include "../headers/Menu.h"
#include <iostream>

bool Menu::exitApplication = false;

void Menu::init() {
    Manager manager = Manager();

    while (!Menu::exitApplication) {

    }
}

void Menu::showMainMenu() {
    std::cout << std::endl;
    std::cout << "------- Main Menu -------" << std::endl;
    std::cout << "[1] Quit and Save" << std::endl;
    std::cout << "[2] Make a request" << std::endl;
    std::cout << "[3] Display information" << std::endl;
    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    while (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(INT32_MAX, '\n');
        std::cout << "[Warning!] Please enter a valid option!";
        showMainMenu();
    }
    switch (choice) {
        case 1: break;
        case 2: break;
        case 3: break;
        default: std::cout << "### [Warning] Please choose from one of the listed numbers ###" << std::endl ; showMainMenu() ;  break;
    }
}