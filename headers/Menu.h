#ifndef PROJETO_AED_2_MENU_H
#define PROJETO_AED_2_MENU_H

#include "Manager.h"

class Menu {

    static bool exitApplication;

    enum MainMenuOptions {
        QUIT_AND_SAVE = 0,
        INFORMATION_ABOUT_AIRPORT = 1 ,
        MIN_PATH = 2,
        BEST_PATHS = 3
    };

    /**
     * wait for user input
     * @param string this is printed to the terminal
     */
    static void wait(const std::string& string);

public:
    /**
     * Initialize the program
     */
    static void init();
    /**
     * displays and manages the main menu of the application
     * @return an integer for the next menu to be displayed
     */
    static int showMainMenu();
    /**
     * @return an integer for the next menu to be displayed
     */
    static int minPath();
    /**
     * @return an integer for the next menu to be displayed
     */
    static int infoAboutAirports();
    static void travelMinAirports(Manager& manager);
    static void travelMinByCity(Manager& manager);
    static void travelMinByCoordinates(Manager& manager);
    static void infoGeneral(Manager &manager);
    static void infoWithMaxFlights(Manager &manager);
    static int bestPaths(Manager &manager);
    static void showAllBestPaths(Manager &manager);
    static void showAllBestPathsAirlines(Manager &manager);
    static void finishExecution();
};

#endif
