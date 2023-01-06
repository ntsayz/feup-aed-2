//
// Created by ntsayz on 12/20/22.
//
/**
    @class Manager
    @brief Manages the application.
    Stores its most important data structures, manages the application state.
*/

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
    /**
	* @brief variable for user input.
	*/
    int option;
    /**
	* @brief variable for user input.
	*/
    int choice;
    /**
	* @brief Controls the global state of the application in the menus.
	*/
    bool globalSession = false;
    /**
	* @brief Controls the local state of the application in functions, menus.
	*/
    bool localSession = false;
    /** @name  Manager's Data Structures */
    /**@{
    *
    */

    /**
	* @brief Hashtable to store airlines. IATA code as key and an airline object as the value.
	*/
    std::unordered_map<std::string,Airline> airlines;
    /**
	* @brief Hashtable to store airports. IATA code as key and an airport object as the value.
	*/
    std::unordered_map<std::string,Airport> airports;
    /**
	* @brief Hashtable to store a concatenated string
     * with a city and its country name as key, for uniqueness. There are multiple cities
     * with the same name in the world, If only cities where stored it would lead to data mix-up
     * A vector of airport objects as values, because a number of cities have multiple airports
	*/
    std::unordered_map<std::string,std::vector<Airport>> cities;
    /**
	* @brief Graph with Airports as nodes and flights as edges that connect them. Stored in an adjacency list
	*/
    Graph flight_network;
    /**
	* @brief List of airports in the city of departure.
	*/
    std::vector<Airport> departuresAirports;
    /**
	* @brief List of airports in the city of arrival.
	*/
    std::vector<Airport> arrivalAirports;
    /**
	* @brief Priority queue to store flights with less distance between them being prioritised
	*/
    std::priority_queue<Flight,std::vector<Flight>, std::greater<>> flights_eq_weight;
    /** @} end of Manager's Data Structures */
public:
    /**
	* @brief Manager's constructor
	*/
    Manager()= default;
    /**
	* @brief Function to start the application, called by the only instance of the manager function.
	*/
    void run();
    void testing();
    /// Function to load the data from the .csv files from the dataset.
    /// \param fname1 Path to 'airlines.csv'
    /// \param fname2 Path to 'airports.csv'
    /// \param fname3 Path to 'flights.csv'
    /// \return It compares the size of the data structures that the data was loaded into, to determine if they're according to spec
    bool loadData(const std::string& fname1, const std::string& fname2, const std::string& fname3);
    /**
   * @brief Displays the main menu.
   */
    void main_menu();
    /// 1st Option in the Main menu; Shows the 'Search Flights' section
    /// \param notARecursiveCall Since we need to use this function multiple times within the same call chain, it should be recursive. This was a way to handle recursion appropriately
    void search_flights_menu(bool notARecursiveCall);
    /// Looks for flights given
    /// \param departures_airports List of airports in the city of departure
    /// \param arrival_airports List of airports in the city of arrival
    void search_flights(std::vector<Airport> departures_airports, std::vector<Airport> arrival_airports);
    /// Gets a list of airports, prompting the user to write the name of the city or/and country of their origin
    /// \return list of airports
    std::vector<Airport> get_airports_by_city_country();
    /// Gets a list of airports, prompting the user to write their IATA code
    /// \return list of airports
    Airport get_airports_by_code();
    /// Gets a list of airports, prompting the user to write coordinates for the desired location
    /// \return list of airports
    std::vector<Airport> get_airports_by_coordinates();
    /// Shows multiple routes with same number of flights
    /// \param departures_airports list of departure airports
    /// \param arrival_airports list of arrival airports
    void show_multiple_routes(const std::vector<Airport> &departures_airports, const std::vector<Airport> &arrival_airports);
    ///  Searches for routes using only one requested airline
    /// \param departures_airports list of departure airports
    /// \param arrival_airports list of arrival airports
    void search_one_airline(const std::vector<Airport> &departures_airports, const std::vector<Airport> &arrival_airports);
    /// Shows detailed route and flight information.
    /// \param departures_airports list of departure airports
    /// \param arrival_airports list of arrival airports
    void show_flight_info(const std::vector<Airport> &departures_airports, const std::vector<Airport> &arrival_airports);
    /// Helper function to get airline code
    /// \return IATA code of airline
    std::string  get_airline_code();
};


#endif //FEUP_AED2_MANAGER_H


/**

    @mainpage SkyPlanner - Flight Search and Management Application
    @section intro_sec Introduction
    SkyPlanner is a flight search and management application that allows users to search for flights between airports, view detailed information about specific airports and airlines, and find the shortest route between two airports.
    @section features_sec Features
        - Search for flights between two airports
        - View detailed information about specific airports and airlines
        - Find the shortest route between two airports
    @section data_sec Data
    SkyPlanner uses data from several CSV files to populate its database of airports and flights. These files should be placed in the same directory as the executable. The required files are:
        airlines.csv: Contains information about different airlines (code, name, callsign, country)
        airports.csv: Contains information about different airports (code, name, city, country, latitude, longitude)
        flights.csv: Contains information about flights between airports (departure airport code, arrival airport code, airline code)
    @section usage_sec Usage
    Once the SkyPlanner application is running, you can use the main menu to access the different features of the application. Follow the prompts to search for flights, view airport and airline information, or manage the database of airports and flights.

*/