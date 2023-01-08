//
// Created by ntsayz on 12/20/22.
//



#include "Utility.h"
#ifdef __cplusplus__
#include <cstdlib>
#else
#include <cstdlib>
#endif




int  Utility::getInput(int choice, int min, int max)  {
    while(true){
        if(choice == 9) return choice;
        if (std::cin.fail()) {
            std::cerr << "Sorry, I cannot read that. Please try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }else if (choice < min || choice > max) {
            return -1;
        }

        return choice;
    }
}

void Utility::clear_screen() {
#ifdef WINDOWS
    std::system("cls");
#endif
}
void Utility::header(const std::string& title){
    int n = (int)(title.size() + 59) / 2;
    std::cout << "|" << std::setfill('-') <<std::setw(59) << "|\n"; // ---
    std::cout << "|" << std::setfill(' ') << std::setw(n); // | txt
    std::cout << title;
    std::cout << std::setfill(' ') <<std::setw(59 -n)<<"|\n"  //  --> |
              << "|"<< std::setfill('-') <<std::setw(59) <<"|\n";
}

void Utility::footer() {
    std::cout << "|" << std::setfill('-') <<std::setw(59) << "|\n"; // --
    std::cout << "|" << std::setfill(' ')<< std::setw(33) << "9.Back  " << std::setw(26) << "|\n";
    std::cout << "|" << std::setfill('-') <<std::setw(59) << "|\n";
    //std::cout << "-->";
}

void Utility::body(const std::string& description, std::vector<std::string> options){
    int n = (int)(description.size() + 59) / 2;
    std::cout << "|" << std::setfill(' ') << std::setw(n) << description;
    std::cout << std::setfill(' ') <<std::setw(59- n)<<"|\n";
    std::cout << "|" << std::setfill(' ') <<std::setw(59) << "|\n";
    for(int i =0; i < options.size(); i++){
        int k = (int)(options[i].size() + 59) / 2;
        std::cout << "|" << std::setfill(' ') << std::setw(k) << options[i] << std::setw(59 - k) << "|\n";
    }

}

bool Utility::isSubstring(std::string str, std::string sub)
{
    return str.find(sub) != std::string::npos;
}

std::string Utility::getCity(){
    std::string stringin;
    while (true){
        Utility::clear_screen();
        Utility::header("SkyPlanner");
        Utility::header("Flight Search - City/Country");
        Utility::body("Write the city/country name",{""});
        Utility::footer();
        std::cout << "-->";
        std::getline(std::cin,stringin);
        if(stringin.empty()){
            continue;
        }else if(stringin == "9" || stringin == "exit"){
            return "exit";
        }else if(stringin.size() < 2){
            std::cerr << "A bit longer please!";
            continue;
        }else{
            return stringin;
        }
    }

}
std::string Utility::getAirportCode(){
    std::string stringin;
    while (true){
        Utility::clear_screen();
        Utility::header("SkyPlanner");
        Utility::header("Flight Search - Airport Code");
        Utility::body("Write the code",{"It should have 3 letters","eg:.MPM"});
        Utility::footer();
        std::cout << "-->";
        std::getline(std::cin,stringin);
        if(stringin.empty()){
            continue;
        }else if(stringin == "9" || stringin == "exit"){
            return "exit";
        }else if(stringin.size() < 3 || stringin.size() >3){
            std::cerr << "That's not the correct format!";
            continue;
        }else{
            return stringin;
        }
    }

}

std::string Utility::getAirline(){
    std::string stringin;
    while (true){
        Utility::clear_screen();
        Utility::header("SkyPlanner");
        Utility::header("Flight Search - Airline");
        Utility::body("Write the airline name",{""});
        Utility::footer();
        std::cout << "-->";
        std::getline(std::cin,stringin);
        if(stringin.empty()){
            continue;
        }else if(stringin == "9" || stringin == "exit"){
            return "exit";
        }else if(stringin.size() < 2){
            std::cerr << "A bit longer please!";
            continue;
        }else{
            return stringin;
        }
    }

}

std::string Utility::getAirlineCode(){
    std::string stringin;
    while (true){
        Utility::clear_screen();
        Utility::header("SkyPlanner");
        Utility::header("Flight Search - Airline Code");
        Utility::body("Write the code",{"It should have 3 letters","eg:.RYR"});
        Utility::footer();
        std::cout << "-->";
        std::getline(std::cin,stringin);
        if(stringin.empty()){
            continue;
        }else if(stringin == "9" || stringin == "exit"){
            return "exit";
        }else if(stringin.size() < 3 || stringin.size() >3){
            std::cerr << "That's not the correct format!";
            continue;
        }else{
            return stringin;
        }
    }

}