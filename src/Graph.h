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
/*
using namespace std;

// Represents an airport
struct Airport {
    std::string name;
    double latitude{};
    double longitude{};
};

// Represents a flight
struct Flight {
    Airport* departure;
    Airport* arrival;
    std::string airline;
};

// Represents a Graph of airports and flights
class Graph {
public:
    void addFlight(const Flight &flight);
    void addAirport(const Airport &airport);
    vector<Airport> GetAirportsWithinDistance(double latitude, double longitude, double max_distance) const;
    int getNumFlightsFromAirport(const Airport &airport) const;
    std::vector<std::vector<Flight>>  FindShortestRoutes(const Airport &departure, const Airport &arrival) const;
    vector<Flight> GetFlightsFromAirportToAirport(const Airport &departure, const Airport &arrival) const;
    vector<vector<Flight>> GetPathsWithOneAirline(const Airport &departure, const Airport &arrival, const string &airline) const;
private:
    std::unordered_map<std::string, Airport> airports;
    std::vector<Flight> flights;
    double getDistance(const Airport &airport1, const Airport &airport2) const;



};*/
#include "Airport.h"
#include "Flight.h"
// Represents a Graph of airports and flights
class Graph {
public:
    void addFlight(const Flight &flight);
    void addAirport(const Airport &airport);
    std::vector<Airport> GetAirportsWithinDistance(double latitude, double longitude, double max_distance) const;
    int getNumFlightsFromAirport(const Airport &airport) const;
    std::vector<std::vector<Flight>>  FindShortestRoutes(const Airport &departure, const Airport &arrival) const;
    std::vector<Flight> FindShortestRoute(const Airport &departure, const Airport &arrival) const;
    //std::vector<std::vector<Flight>> GetFlightsFromAirportToAirport(const Airport &departure, const Airport &arrival) const;
    std::vector<std::vector<Flight>> GetPathsWithOneAirline(const Airport &departure, const Airport &arrival, const std::string &airline) const;

private:
    // Adjacency list representation of the graph
    std::unordered_map<std::string, std::vector<Flight>> adjacency_list;
    // Map from airport names to airport objects
    std::unordered_map<std::string, Airport> airports;

    double getDistance(const Airport &airport1, const Airport &airport2) const;
};




#endif //FEUP_AED2_GRAPH_H
