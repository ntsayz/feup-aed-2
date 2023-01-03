//
// Created by ntsayz on 12/20/22.
//

#include "Airport.h"

#include <utility>

void Airport::setLatitude(double latitude) {
    Airport::latitude = latitude;
}

void Airport::setLongitude(double longitude) {
    Airport::longitude = longitude;
}

const std::string &Airport::getCountry() const {
    return country;
}

const std::string &Airport::getIata() const {
    return IATA;
}

const std::string &Airport::getName() const {
    return name;
}

const std::string &Airport::getCity() const {
    return city;
}

double Airport::getLatitude() const {
    return latitude;
}

double Airport::getLongitude() const {
    return longitude;
}

Airport::Airport() {

}
