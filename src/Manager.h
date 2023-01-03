//
// Created by ntsayz on 12/20/22.
//
#include <iostream>
#include "Graph.h"
#include "Airlines.h"
#include "Menu.h"
#include "Utility.h"
#include <openssl/sha.h>

#ifndef FEUP_AED2_MANAGER_H
#define FEUP_AED2_MANAGER_H


class Manager {
private:
    int option, choice;
    bool globalSession = false;
    bool localSession = false;
    std::unordered_map<std::string,Airline> airlines;
    std::unordered_map<std::string,Airport> airports;
    std::unordered_map<std::string,std::vector<Airport>> cities;
    Graph flight_network;
    std::vector<Airport> departuresAirports,arrivalAirports;
public:
    Manager()= default;
    void run();
    void testing();
    bool loadData(const std::string& fname1, const std::string& fname2, const std::string& fname3);

    void main_menu();

    void search_flights_menu(bool notARecursiveCall);

    void search_flights(std::vector<Airport> departures_airports, std::vector<Airport> arrival_airports);

    std::vector<Airport> getAirportsCityCountry();

    Airport getAirportByCode();

    std::vector<Airport> getAirportsByCoordinates();


    void show_flight_info(const std::vector<Airport>& departures_airports, const std::vector<Airport>& arrival_airports,
                          const std::vector<Flight>& route);
};


#endif //FEUP_AED2_MANAGER_H
