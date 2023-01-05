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
    std::priority_queue<std::vector<Flight>,std::vector<std::vector<Flight>>, std::greater<>> flights_eq_weight;
public:
    Manager()= default;
    ///
    void run();
    void testing();
    ///
    /// \param fname1
    /// \param fname2
    /// \param fname3
    /// \return true if the vectors size is equivalent to the number of lines in the files
    bool loadData(const std::string& fname1, const std::string& fname2, const std::string& fname3);
    ///
    void main_menu();
    ///
    /// \param notARecursiveCall
    void search_flights_menu(bool notARecursiveCall);
    ///
    /// \param departures_airports
    /// \param arrival_airports
    void search_flights(std::vector<Airport> departures_airports, std::vector<Airport> arrival_airports);
    ///
    /// \return list of Airports
    std::vector<Airport> get_airports_by_city_country();
    ///
    /// \return
    Airport get_airports_by_code();
    ///
    /// \return
    std::vector<Airport> get_airports_by_coordinates();
    ///
    /// \param departures_airports
    /// \param arrival_airports
    void show_multiple_routes(const std::vector<Airport> &departures_airports, const std::vector<Airport> &arrival_airports);

    void search_one_airline(const std::vector<Airport> &departures_airports, const std::vector<Airport> &arrival_airports);

    void show_flight_info(const std::vector<Airport> &departures_airports, const std::vector<Airport> &arrival_airports);
};


#endif //FEUP_AED2_MANAGER_H


/*! \mainpage SkyPlanner - 2nd AED Project (FEUP)
 *
 * \section intro_sec Introduction
 *
 * This is the introduction.
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Opening the box
 *
 * etc...
 */