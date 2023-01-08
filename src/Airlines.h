//
// Created by ntsayz on 12/20/22.
//

#ifndef FEUP_AED2_AIRLINES_H
#define FEUP_AED2_AIRLINES_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <string>
/**
    @class Airline
    @brief Represents an airline
*/
class Airline {
private:
    /**
    @brief The code of the airline
    */
    std::string code;
    /**
    @brief The name of the airline
    */
    std::string name;
    /**
    @brief The callsign of the airline
    */
    std::string callsign;
    /**
    @brief The country of the airline
    */
    std::string country;
public:
    /**
    * @brief Constructs an Airline object with the given code, name, callsign, and country
    * @param code The code of the airline
    * @param name The name of the airline
    * @param callsign The callsign of the airline
    * @param country The country of the airline
    */
    Airline(std::string code, std::string name, std::string callsign, std::string country) :
            code(std::move(code)), name(std::move(name)), callsign(std::move(callsign)), country(std::move(country)) {}

    /**
    * @brief Creates an Airline object from a string in .csv format
    * @param iss An std::istringstream object containing the .csv string
    * @return The constructed Airline object
    */
    static Airline fromCSVLine(std::istringstream& iss) {
        std::string code, name, callsign, country;

        std::getline(iss, code, ',');
        std::getline(iss, name, ',');
        std::getline(iss, callsign, ',');
        std::getline(iss, country);

        return {code, name, callsign, country};
    }

    /**
    * @brief Gets the code of the airline
    * @return The code of the airline
    */
    const std::string &getCode() const;

    /**
    * @brief Gets the name of the airline
    * @return The name of the airline
    */
    const std::string &getName() const;

    /**
    * @brief Gets the callsign of the airline
    * @return The callsign of the airline
    */
    const std::string &getCallsign() const;

    /**
    * @brief Gets the country of the airline
    * @return The country of the airline
    */
    const std::string &getCountry() const;
};

#endif //FEUP_AED2_AIRLINES_H
