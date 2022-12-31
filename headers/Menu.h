#ifndef PROJETO_AED_2_MENU_H
#define PROJETO_AED_2_MENU_H

#include "Manager.h"

class Menu {

    static bool exitApplication;

    enum MainMenuOptions {
        QUIT_AND_SAVE = 1,
        MAKE_A_REQUEST = 2 ,
        DISPLAY_INFORMATION = 3,
        MIN_PATH_TEST = 4
    };

    static void wait(const std::string& string);

public:
    /**
     * Initialize the program
     */
    static void init();
    /// @brief displays and manages the main menu of the application
    static int showMainMenu();
    static void travelMinAirports(Manager& manager);
};

#endif
