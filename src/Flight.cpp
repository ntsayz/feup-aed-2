//
// Created by ntsayz on 12/20/22.
//

#include "Flight.h"

const std::string &Flight::getDeparture() const {
    return departure;
}

const std::string &Flight::getArrival() const {
    return arrival;
}

const std::string &Flight::getAirline() const {
    return airline;
}

void Flight::setDistance(double distance) {
    this->distance = distance;
}

double Flight::getDistance() const {
    return distance;
}

