#ifndef PROJETO_AED_2_MENU_H
#define PROJETO_AED_2_MENU_H

#include "Manager.h"

class Menu {

    static bool exitApplication;

    enum MainMenuOptions {
        QUIT_AND_SAVE = 0,
        INFORMATION_ABOUT_AIRPORT = 1 ,
        MAKE_A_REQUEST = 2,
        MIN_PATH = 3
    };

    static void wait(const std::string& string);

public:
    /**
     * Initialize the program
     */
    static void init();
    /// @brief displays and manages the main menu of the application
    static int showMainMenu();
    static int infoAboutAirports(Manager& manager);
    static void travelMinAirports(Manager& manager);
    static void infoGeneral(Manager &manager);
    static void infoWithMaxFlights(Manager &manager);
    static void finishExecution();
};

#endif
