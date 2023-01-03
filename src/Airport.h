//
// Created by ntsayz on 12/20/22.
//
#ifndef FEUP_AED2_AIRPORT_H
#define FEUP_AED2_AIRPORT_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <string>

class Airport {
private:
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    double latitude;
    double longitude;
public:
    Airport();
    Airport(std::string IATA) : code(std::move(IATA)) {}
    Airport(std::string code, std::string name, std::string city, std::string country, double latitude, double longitude) :
            code(std::move(code)), name(std::move(name)), city(std::move(city)), country(std::move(country)), latitude(latitude), longitude(longitude) {}

    static Airport fromCSVLine(std::istringstream& iss) {
        std::string code, name, city, country;
        double latitude, longitude;

        std::getline(iss, code, ',');
        std::getline(iss, name, ',');
        std::getline(iss, city, ',');
        std::getline(iss, country, ',');

        std::string latitudeString, longitudeString;
        std::getline(iss, latitudeString, ',');
        std::getline(iss, longitudeString);

        std::stringstream(latitudeString) >> latitude;
        std::stringstream(longitudeString) >> longitude;

        return Airport(code, name, city, country,latitude,longitude);
    }

    const std::string &getCountry() const;

    const std::string &getCode() const;

    const std::string &getName() const;

    const std::string &getCity() const;

    double getLatitude() const;

    double getLongitude() const;

    void setLatitude(double latitude);

    void setLongitude(double longitude);
};

#endif //FEUP_AED2_AIRPORT_H
