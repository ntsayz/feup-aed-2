//
// Created by ntsayz on 12/21/22.
//

#ifndef FEUP_AED2_MENU_H
#define FEUP_AED2_MENU_H

/**
    @class Menu
    @brief Prints the menu and avoids bloating the Manager class
*/
class Menu {
private:
public:
    static int Main();

    static int Search(bool departure);

    static int Search_CC();

    static int show(bool show);
};


#endif //FEUP_AED2_MENU_H
