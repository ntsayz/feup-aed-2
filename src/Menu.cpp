//
// Created by ntsayz on 12/21/22.
//

#include "Menu.h"
#include "Utility.h"

int Menu::Main() {
    int choice;
    Utility::header("SkyPlanner");
    Utility::header("Main Menu");
    Utility::body("Choose",{"1. Search for flights","2. Show data"});
    Utility::footer();
    std::cin >> choice;
    Utility::clear_screen();
    return Utility::getInput(choice,1,2);
}

int Menu::Search(bool departure){
    int choice;
    std::string d = "What is your departure location?";
    if(!departure){
        d = "What is your arrival location?";
    }
    Utility::header("SkyPlanner");
    Utility::header("Flight Search");
    Utility::body(d,
    {"1. Search by city/country name","2. Search by airport code code","3. Search by geographical coordinates"});
    Utility::footer();
    std::cin >> choice;
    Utility::clear_screen();
    return Utility::getInput(choice,1,3);
}

int Menu::Search_CC(){
    int choice;
    Utility::header("SkyPlanner");
    Utility::header("Flight Search - City/Country");
    Utility::body("Write the city/country name",{""});
    std::cout << "-->";
    std::cin >> choice;
    Utility::clear_screen();
    return Utility::getInput(choice,1,2);
}

int Menu::show(bool show) {
    int choice;
    Utility::body("Choose",
                  {"1. Number of flights of an airport ","2. Airlines of an airport","3. All possible destinations of an airport","4. Airports reachable using a certain number of flights","5. Show data"});
    Utility::footer();
    std::cin >> choice;
    Utility::clear_screen();
    return Utility::getInput(choice,1,5);
}
