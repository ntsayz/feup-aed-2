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


class Flight {
private:
    std::string departure;
    std::string arrival;
    std::string airline;
    double distance;
public:

    Flight(std::string source, std::string target, std::string airline) :
            departure(std::move(source)), arrival(std::move(target)), airline(std::move(airline)) {}

    static Flight fromCSVLine(std::istringstream& iss) {
        std::string source, target, airline;

        std::getline(iss, source, ',');
        std::getline(iss, target, ',');
        std::getline(iss, airline);

        return {source, target, airline};
    }
    void setDistance(double distance);

    const std::string &getDeparture() const;

    const std::string &getArrival() const;

    const std::string &getAirline() const;

    double getDistance() const;
    bool operator<(Flight f2){
        return this->distance < f2.distance;
    }
};


#endif //FEUP_AED2_FLIGHT_H
