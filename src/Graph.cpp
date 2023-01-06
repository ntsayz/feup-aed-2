//
// Created by ntsayz on 12/20/22.
//

#include "Graph.h"

// Adds a flight to the graph
void Graph::addFlight(const Flight &flight) {
    // Add the flight to the adjacency list
    adjacency_list[flight.getDeparture()].push_back(flight);
}

// Adds an airport to the graph
void Graph::addAirport(const Airport &airport) {
    airports[airport.getCode()] = airport;
}

// Returns a list of airports within a certain distance of a given latitude and longitude , distance in km
std::vector<Airport> Graph::getAirportsWithinDistance(double latitude, double longitude, double max_distance) const {
    std::vector<Airport> nearby_airports;

    for (const auto &[code, airport] : airports) {
        Airport airport1;
        airport1.setLatitude(latitude);
        airport1.setLongitude(longitude);
        double distance = getDistance(airport, airport1);
        if (distance <= max_distance) {
            nearby_airports.push_back(airport);
        }
    }
    return nearby_airports;
}

// Returns the number of flights from a given airport
int Graph::getNumFlightsFromAirport(const Airport &airport) const {
    return adjacency_list.count(airport.getCode()) ? adjacency_list.at(airport.getCode()).size() : 0;
}

std::vector<std::vector<Flight>> Graph::findShortestRoutes(const Airport &departure, const Airport &arrival) const {
    // Use an unordered_set to keep track of visited airports
    std::unordered_set<std::string> visited;

    // Use a queue to perform BFS
    std::queue<std::pair<Airport, std::vector<Flight>>> queue;
    queue.emplace(departure, std::vector<Flight>());

    std::vector<std::vector<Flight>> shortest_routes;

    // Set the minimum number of flights to the maximum possible value
    int min_flights = INT32_MAX;

    while (!queue.empty()) {
        auto [airport, route] = queue.front();
        queue.pop();

        // If we have reached the destination airport, return the route
        if (airport.getCode() == arrival.getCode()) {
            if (route.size() < min_flights) {
                shortest_routes.clear();
                min_flights = route.size();
            }
            // If the number of flights in this route is equal to the minimum, add it to the list of the shortest routes
            if (route.size() == min_flights) {
                shortest_routes.push_back(route);
                if(shortest_routes.size() == 50){ // this is capped bc it was taking too long to run
                    return shortest_routes;
                }
            }
        }

        // Mark the airport as visited
        visited.insert(airport.getCode());

        // Add all the flights from this airport to the queue
        if (adjacency_list.count(airport.getCode()) > 0) {
            for (const auto &flight: adjacency_list.at(airport.getCode())) {
                if (visited.count(flight.getArrival()) == 0) {
                    // Create a new route by adding the current flight to the existing route
                    auto new_route = route;
                    new_route.push_back(flight);
                    queue.emplace(flight.getArrival(), new_route);//*bf arr
                }
            }
        }
    }

    return shortest_routes;
}

std::vector<Flight> Graph::findShortestRoute(const Airport &departure, const Airport &arrival) const {
    // Use an unordered_set to keep track of visited airports
    std::unordered_set<std::string> visited;

    // Use a queue to perform BFS
    std::queue<std::pair<Airport, std::vector<Flight>>> queue;
    queue.emplace(departure, std::vector<Flight>());

    // Set the minimum number of flights to the maximum possible value
    int min_flights = INT32_MAX;

    while (!queue.empty()) {
        auto [airport, route] = queue.front();
        queue.pop();

        // If we have reached the destination airport, return the route
        if (airport.getCode() == arrival.getCode()) {
            if (route.size() < min_flights) {
                min_flights = route.size();
                return route;
            }
        }

        // Mark the airport as visited
        visited.insert(airport.getCode());

        // Add all the flights from this airport to the queue
        if (adjacency_list.count(airport.getCode()) > 0) {
            for (const auto &flight: adjacency_list.at(airport.getCode())) {
                if (visited.count(flight.getArrival()) == 0) {
                    // Create a new route by adding the current flight to the existing route
                    auto new_route = route;
                    new_route.push_back(flight);
                    queue.emplace(flight.getArrival(), new_route);
                }
            }
        }
    }

    // If we reach here, it means no route was found
    return std::vector<Flight>{};
}



double Graph::getDistance(const Airport &airport1, const Airport &airport2) const {
    static constexpr double EARTH_RADIUS_KM = 6371.0;

    double lat1 = airport1.getLatitude()* M_PI / 180.0;
    double lon1 = airport1.getLongitude()* M_PI / 180.0;
    double lat2 = airport2.getLatitude() * M_PI / 180.0;
    double lon2 = airport2.getLongitude() * M_PI / 180.0;

    double delta_lat = lat2 - lat1;
    double delta_lon = lon2 - lon1;

    double a = std::sin(delta_lat / 2) * std::sin(delta_lat / 2) +
               std::cos(lat1) * std::cos(lat2) *
               std::sin(delta_lon / 2) * std::sin(delta_lon / 2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    return EARTH_RADIUS_KM * c;
}


std::vector<std::vector<Flight>> Graph::getPathsWithOneAirline(const Airport &departure, const Airport &arrival, const std::string &airline) const {
    std::vector<std::vector<Flight>> paths;

    // Use a queue to store the paths we are currently exploring
    std::queue<std::vector<Flight>> queue;
    // Push the initial path with just the departure airport onto the queue
    queue.push({});

    // Use a set to store the airports we have already visited in our search
    std::unordered_set<std::string> visited;
    visited.insert(departure.getCode());

    while (!queue.empty()) {
        // Get the next path from the queue
        auto current_path = queue.front();
        queue.pop();

        // Get the current airport from the end of the path
        auto current_airport = current_path.empty() ? departure.getCode() : current_path.back().getArrival();

        // If we have reached the destination airport, add the path to the list of paths
        if (current_airport == arrival.getCode()) {
            paths.push_back(current_path);
            continue;
        }

        // Add all the flights from the current airport to the queue
        for (const auto &flight: adjacency_list.at(current_airport)) {
            // If we have already visited the destination airport of this flight, skip it
            if (visited.count(flight.getArrival()) > 0) {
                continue;
            }

            // If the flight is not from the specified airline, skip it
            if (flight.getAirline() != airline) {
                continue;
            }

            // Create a new path by adding the current flight to the existing path
            auto new_path = current_path;
            new_path.push_back(flight);
            // Mark the destination airport as visited
            visited.insert(flight.getArrival());
            queue.push(new_path);
        }
    }

    return paths;
}

