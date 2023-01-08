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
/**
    @class Airport
    @brief Represents an airport
*/
class Airport {
private:
private:
    /**
    * @brief The code of the airport
    */
    std::string code;
    /**
    * @brief The name of the airport
    */
    std::string name;
    /**
    * @brief The city of the airport
    */
    std::string city;
    /**
    * @brief The country of the airport
    */
    std::string country;
    /**
    * @brief The latitude of the airport
    */
    double latitude;
    /**
    * @brief The longitude of the airport
    */
    double longitude;
public:
    /**
    * @brief Constructs an Airport object with default values
    */
    Airport();
    /**
    * @brief Constructs an Airport object with the given code
    * @param IATA The code of the airport
    */
    Airport(std::string IATA) : code(std::move(IATA)) {}
    /**
    * @brief Constructs an Airport object with the given code, name, city, country, latitude, and longitude
    * @param code The code of the airport
    * @param name The name of the airport
    * @param city The city of the airport
    * @param country The country of the airport
    * @param latitude The latitude of the airport
    * @param longitude The longitude of the airport
    */
    Airport(std::string code, std::string name, std::string city, std::string country, double latitude, double longitude) :
            code(std::move(code)), name(std::move(name)), city(std::move(city)), country(std::move(country)), latitude(latitude), longitude(longitude) {}

    /**
        @brief Creates an Airport object from a string in .csv format
        @param iss An std::istringstream object containing the string
        @return The airport object
    */

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

    /**
        @brief Gets the country of the airport
        @return The country of the airport
    */
    const std::string &getCountry() const;
    /**
        @brief Gets the code of the airport
        @return The code of the airport
    */
    const std::string &getCode() const;

    /**
        @brief Gets the name of the airport
        @return The name of the airport
    */
    const std::string &getName() const;

    /**
        @brief Gets the city of the airport
        @return The city of the airport
    */
    const std::string &getCity() const;

    /**
        @brief Gets the latitude of the airport
        @return The latitude of the airport
    */
    double getLatitude() const;

    /**
        @brief Gets the longitude of the airport
        @return The longitude of the airport
    */
    double getLongitude() const;

    /**
        @brief Sets the latitude of the airport
        @param latitude The new latitude of the airport
    */
    void setLatitude(double latitude);

    /**
        @brief Sets the longitude of the airport
        @param longitude The new longitude of the airport
    */
    void setLongitude(double longitude);

};

#endif //FEUP_AED2_AIRPORT_H
