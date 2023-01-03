#include "../headers/Menu.h"
#include <iostream>

bool Menu::exitApplication = false;

void Menu::init() {
    Manager manager = Manager();

    std::atexit(Menu::finishExecution);

    while (!Menu::exitApplication) {
        int option = Menu::showMainMenu();

        switch (option) {
            case QUIT_AND_SAVE:
                Menu::exitApplication = true;
                break;
            case INFORMATION_ABOUT_AIRPORT:
                option = Menu::infoAboutAirports(manager);

                switch(option) {
                    case 0:
                        break;
                    case 1:
                        Menu::numFlights(manager);
                        break;
                    case 2:
                        Menu::numAirLines(manager);
                        break;
                    case 3:
                        Menu::numDestinations(manager);
                        break;
                    case 4:
                        Menu::numCountries(manager);
                        break;
                    default:
                        std::cout << "Please choose a valid option.";
                        break;
                }

            case MAKE_A_REQUEST:
                break;
            case MIN_PATH:
                Menu::travelMinAirports(manager);
                break;
            default:
                std::cout << "Please choose a valid option.";
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
    std::cout << "[0] Quit and Save" << std::endl;
    std::cout << "[1] Information About Airports" << std::endl;
    std::cout << "[2] ±±±" << std::endl;
    std::cout << "[3] Min Path" << std::endl;

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

int Menu::infoAboutAirports(Manager& manager) {
    int choice;

    std::cout << "\tWhat information would you like to view?\n";
    std::cout << "\t[0] Back to main menu\n";
    std::cout << "\t[1] How many flights from an airport\n";
    std::cout << "\t[2] How many Air Companies have flights from an airport\n";
    std::cout << "\t[3] How many destinations from an airport\n";
    std::cout << "\t[4] How many countries from an airport\n";
    std::cin >> choice;

    if (!std::cin) exit(0);

    std::cout.flush();

    return choice;
}

void Menu::numFlights(Manager& manager) {
    manager.printNumOfFlights();
    Menu::wait("\n\t[press ENTER to continue]");
}

void Menu::numAirLines(Manager &manager) {
    manager.printNumAirCompanies();
    Menu::wait("\n\t[press ENTER to continue]");
}

void Menu::numDestinations(Manager &manager) {
    manager.printNumDestinations();
    Menu::wait("\n\t[press ENTER to continue]");
}

void Menu::numCountries(Manager &manager) {
    manager.printNumCountries();
    Menu::wait("\n\t[press ENTER to continue]");
}

void Menu::finishExecution() {
    Menu::wait("\n\tFinished execution. Press [ENTER] to leave.");
}