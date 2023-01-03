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

// Class to represent an airline
class Airline {
public:
    std::string code;
    std::string name;
    std::string callsign;
    std::string country;

    Airline(std::string code, std::string name, std::string callsign, std::string country) :
            code(std::move(code)), name(std::move(name)), callsign(std::move(callsign)), country(std::move(country)) {}


    static Airline fromCSVLine(std::istringstream& iss) {
        std::string code, name, callsign, country;

        std::getline(iss, code, ',');
        std::getline(iss, name, ',');
        std::getline(iss, callsign, ',');
        std::getline(iss, country);

        return {code, name, callsign, country};
    }

    const std::string &getCode() const;

    const std::string &getName() const;

    const std::string &getCallsign() const;

    const std::string &getCountry() const;
};

#endif //FEUP_AED2_AIRLINES_H
