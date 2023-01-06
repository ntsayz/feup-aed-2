//
// Created by ntsayz on 12/20/22.
//

#ifndef FEUP_AED2_FLIGHT_H
#define FEUP_AED2_FLIGHT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <string>

/**
    @class Flight
    @brief Represents a flight between two airports
*/

class Flight {
private:
    /**
    * @brief The code of the airport where the flight departs from
    */
    std::string departure;
    /**
    * @brief The code of the airport where the flight arrives at
    */
    std::string arrival;
    /**
    * @brief The code of the airline operating the flight
    */
    std::string airline;
    /**
    * @brief The distance of the flight
    */
    double distance;
public:

    Flight(std::string source, std::string target, std::string airline) :
            departure(std::move(source)), arrival(std::move(target)), airline(std::move(airline)) {}
    /**
    * @brief Creates a Flight object from a string in .csv format
    * @param iss An std::istringstream object containing the .csv string
    * @return The flight object
    */
    static Flight fromCSVLine(std::istringstream& iss) {
        std::string source, target, airline;

        std::getline(iss, source, ',');
        std::getline(iss, target, ',');
        std::getline(iss, airline);

        return {source, target, airline};
    }
    /**
    * @brief Sets the distance of the flight
    * @param distance The new distance of the flight
    */
    void setDistance(double distance);

    /**
     * @brief Gets the code of the airport where the flight departs from
     * @return The code of the airport where the flight departs from
     */
    const std::string &getDeparture() const;

    /**
    * @brief Gets the code of the airport where the flight arrives at
    * @return The code of the airport where the flight arrives at
    */
    const std::string &getArrival() const;

    /**
    * @brief Gets the code of the airline operating the flight
    * @return The code of the airline operating the flight
    */
    const std::string &getAirline() const;

    double getDistance() const;
    bool operator<(Flight f2){
        return this->distance < f2.distance;
    }
};


#endif //FEUP_AED2_FLIGHT_H
