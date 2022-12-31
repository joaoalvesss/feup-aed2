#include <iostream>
#include "headers/Menu.h"

void menuTest() {
    Menu::init();
}

void Test() {
    Manager manager = Manager();
    manager.printMinPath();
}

int main() {
    //menuTest();
    Test();
    return 0;
}
