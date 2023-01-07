//
// Created by ntsayz on 12/20/22.
//
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <limits>

#ifndef FEUP_AED2_UTILITY_H
#define FEUP_AED2_UTILITY_H

/**
    @class Utility
    @brief Seeing that a lot of functionality is used very often, to avoid repeated code we created a helper class that encapsulated and made our easier throughout the development of this application
*/


class Utility {
public:
    /// Auxiliary function, to get a number from user input given a range
    /// \param choice
    /// \param min
    /// \param max
    /// \return
    static int getInput(int choice, int min, int max);
    /// Auxiliary function, to get a number from user input
    /// \param code
    /// \return
    static int getCode(int code);
    /**
	* @brief Clear screen (Cross-Platform)
	*/
    static void clear_screen();
    /**
	* @brief Auxiliary function, to print the menu's footer
	*/
    static void footer();
    /**
	* @brief Auxiliary function, to print the menu's header
	*/
    static void header(const std::string& title);
    /**
	* @brief Auxiliary function, to print the menu's body
	*/
    static void body(const std::string& description, std::vector<std::string> options);
    /// Checks if a string is contained in another
    /// \param str String to check
    /// \param sub Substring
    /// \return
    static bool isSubstring(std::string str, std::string sub);
    /// Auxiliary function to get city input from user
    /// \return user input
    static std::string getCity();
    /// Auxiliary function to get airport code input from user
    /// \return user input
    static std::string getAirportCode();
    /// Auxiliary function to get airline code input from user
    /// \return user input
    static std::string getAirlineCode();
    /// Auxiliary function to get airline name from user
    /// \return user input
    static std::string getAirline();
    /// Loads data from the .csv files
    /// \tparam T Guarantees that any datatype can be used
    /// \param filename
    /// \return
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
