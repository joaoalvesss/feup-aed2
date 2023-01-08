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
                option = Menu::infoAboutAirports();

                switch(option) {
                    case 0:
                        break;
                    case 1:
                        Menu::infoGeneral(manager);
                        break;
                    case 2:
                        Menu::infoWithMaxFlights(manager);
                        break;
                    default:
                        std::cout << "Please choose a valid option.";
                        break;
                }
                break;

            case MIN_PATH:
                option = Menu::minPath();

                switch (option) {
                    case 1:
                        Menu::travelMinAirports(manager);
                        break;
                    case 2:
                        Menu::travelMinByCity(manager);
                        break;
                    case 3:
                        Menu::travelMinByCoordinates(manager);
                        break;
                    default:
                        std::cout << "Please choose a valid option.";
                        break;
                }
                break;

            case BEST_PATHS:
                option = Menu::bestPaths(manager);

                switch (option) {
                    case 0:
                        break;
                    case 1:
                        Menu::showAllBestPaths(manager);
                        break;
                    case 2:
                        Menu::showAllBestPathsAirlines(manager);
                        break;
                    default:
                        std::cout << "Please choose a valid option.";
                        break;
                }
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
    if (std::cin.peek() == '\n') std::cin.ignore(50, '\n');
}

int Menu::showMainMenu() {
    int choice;

    std::cout << std::endl;
    std::cout << "\t--------------- MAIN MENU ---------------\n";
    std::cout << "\t[0] Quit and Save\n";
    std::cout << "\t[1] Information About Airports\n";
    std::cout << "\t[2] Best way to flight between two locals\n";
    std::cout << "\t[3] Best possible paths between two airports\n";

    std::cout << "\tEnter your choice: ";
    std::cin >> choice;

    if (!std::cin)
        exit(0);

    std::cout.flush();
    std::cout << "\n\n";
    std::cout.flush();

    return choice;
}

int Menu::minPath() {
    int choice;
    std::cout << "\tWhat do you want to consider a local?\n";
    std::cout << "\t[1] An airport\n";
    std::cout << "\t[2] A city\n";
    std::cout << "\t[3] Location by coordinates\n";
    std::cout << "\t> ";
    std::cin >> choice;
    if (!std::cin) exit(0);

    std::cout.flush();
    std::cout << "\n\n";
    std::cout.flush();

    return choice;
}

void Menu::travelMinAirports(Manager& manager) {
    manager.printMinPath();
    Menu::wait("\n\t[press ENTER to continue]");
}

void Menu::travelMinByCity(Manager& manager) {
    manager.travelByCities();
    Menu::wait("\n\t[press ENTER to continue]");
}

void Menu::travelMinByCoordinates(Manager& manager) {
    manager.travelByCoords();
    Menu::wait("\n\t[press ENTER to continue]");
}

int Menu::infoAboutAirports() {
    int choice;

    std::cout << "\tWhat information would you like to view?\n";
    std::cout << "\t[0] Back to main menu\n";
    std::cout << "\t[1] General information\n";
    std::cout << "\t[2] Information with max number of flights\n";
    std::cout << "\t> ";
    std::cin >> choice;
    if (!std::cin) exit(0);

    std::cout.flush();
    std::cout << "\n\n";
    std::cout.flush();

    return choice;
}

void Menu::infoGeneral(Manager &manager) {
    manager.printAirportGeneralInfo();
    Menu::wait("\n\t[press ENTER to continue]");
}

void Menu::infoWithMaxFlights(Manager &manager) {
    manager.printAirportInfoMaxFlights();
    Menu::wait("\n\t[press ENTER to continue]");
}

int Menu::bestPaths(Manager &manager) {
    int choice;

    std::cout << "\tChoose one:\n";
    std::cout << "\t[0] Back to main menu\n";
    std::cout << "\t[1] Show all best paths\n";
    std::cout << "\t[2] Show all best paths with chosen airlines\n";
    std::cout << "\t> ";
    std::cin >> choice;
    if (!std::cin) exit(0);

    std::cout.flush();
    std::cout << "\n\n";
    std::cout.flush();


    return choice;
}

void Menu::showAllBestPaths(Manager &manager) {
    manager.printBestPaths();
    Menu::wait("\n\t[press ENTER to continue]");
}

void Menu::showAllBestPathsAirlines(Manager &manager) {
    manager.printBestPathsExcludingAirlines();
    Menu::wait("\n\t[press ENTER to continue]");
}

void Menu::finishExecution() {
    Menu::wait("\tFinished execution. Press [ENTER] to quit.");
}