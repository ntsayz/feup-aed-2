//
// Created by ntsayz on 12/20/22.
//

#ifndef FEUP_AED2_GRAPH_H
#define FEUP_AED2_GRAPH_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
#include <cmath>
#include <iostream>
#include <bits/stdc++.h>
#include "Airport.h"
#include "Flight.h"
/**

    @class Graph
    @brief Represents a Graph of airports and flights.
*/
class Graph {
public:
    /**
    * @brief Adds a flight to the graph
    * @param flight The flight to be added
    */
    void addFlight(const Flight &flight);
    /**
    * @brief Adds an airport to the graph
    * @param airport The airport to be added
    */
    void addAirport(const Airport &airport);
    /**
    * @brief Gets a list of airports within a certain distance of a given latitude and longitude
    * @param latitude The latitude of the reference point
    * @param longitude The longitude of the reference point
    * @param max_distance The maximum distance from the reference point
    * @return A vector of airports within the specified distance of the reference point
    */
    std::vector<Airport> getAirportsWithinDistance(double latitude, double longitude, double max_distance) const;
    /**
    * @brief Gets the number of flights from a given airport
    * @param airport The airport to check
    * @return The number of flights from the given airport
    */
    int getNumFlightsFromAirport(const Airport &airport) const;
    /**
    * @brief Finds all shortest routes between two airports using BFS
    * @param departure The airport of departure
    * @param arrival The airport of arrival
    * @return A vector of vector of flights representing all shortest routes between the two airports
    */
    std::vector<std::vector<Flight>> findShortestRoutes(const Airport &departure, const Airport &arrival) const;
    /**
    * @brief Finds the shortest route between two airports using BFS
    * @param departure The airport of departure
    * @param arrival The airport of arrival
    * @return A vector of flights representing the shortest route between the two airports
    */
    std::vector<Flight> findShortestRoute(const Airport &departure, const Airport &arrival) const;
    /**
    * @brief Finds all routes between two airports that use only flights from a given airline using BFS
    * @param departure The airport of departure
    * @param arrival The airport of arrival
    * @param airline The airline to use for all flights in the routes
    * @return A vector of vector of flights representing all routes between the two airports that use only flights from the given airline
    */
    std::vector<std::vector<Flight>> getPathsWithOneAirline(const Airport &departure, const Airport &arrival, const std::string &airline) const;
        /**
    * @brief Gets the distance between two airports using heaviside's formula
    * @param airport1 The first airport
    * @param airport2 The second airport
    * @return The distance between the two airports
    */

    double getDistance(const Airport &airport1, const Airport &airport2) const;
    std::vector<Airport> getReachableAirports(const std::string &start_airport_code, int num_flights) const;
    private:
    /**
     * @brief Adjacency list representing all airports codes (key), as nodes and flights (values) as edges.
     */
    std::unordered_map<std::string, std::vector<Flight>> adjacency_list;
    /**
     * @brief Hashtable with airports codes being mapped to their objects
     */
    std::unordered_map<std::string, Airport> airports;



};




#endif //FEUP_AED2_GRAPH_H
