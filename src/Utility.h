//
// Created by ntsayz on 12/20/22.
//
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>

#ifndef FEUP_AED2_UTILITY_H
#define FEUP_AED2_UTILITY_H


class Utility {
public:

    static int getInput(int choice, int min, int max);
    /// Validates Students code
    static int getCode(int code);
    /// Clear screen (Cross-Platform)
    static void clear_screen();
    /// Auxiliary function, to print the menu's footer
    static void footer();
    /// Auxiliary function, to print the menu's header
    static void header(const std::string& title);
    /// Auxiliary function, to print the menu's body
    static void body(const std::string& description, std::vector<std::string> options);
    static bool isSubstring(std::string str, std::string sub);
    static std::string getCity();
    static std::string getAirportCode();
    static std::string getAirlineCode();
    static std::string getAirline();

    template <typename T>
    static std::vector<T> loadDataFromCSV(std::string filename) {
        std::vector<T> data;
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return data;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            T object = T::fromCSVLine(iss);
            data.push_back(object);
        }

        return data;
    }



};


#endif //FEUP_AED2_UTILITY_H
