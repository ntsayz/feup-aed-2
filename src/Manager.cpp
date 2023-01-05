//
// Created by ntsayz on 12/20/22.
//

#include "Manager.h"


void Manager::run(){
    bool dataLoaded = loadData("../src/dataset/airlines.csv", "../src/dataset/airports.csv", "../src/dataset/flights.csv");
    if(!dataLoaded){
        return;
    }
    main_menu();

}

void Manager::main_menu(){
    globalSession = true;
    while (globalSession){
        Utility::clear_screen();
        switch (Menu::Main()) {
            case 1:
                search_flights_menu(true);
                break;
            case 9:
                globalSession = false;
        }
    }
}
void Manager::search_flights_menu(bool notARecursiveCall){
    localSession = true;
    while(localSession){
        Utility::clear_screen();
        switch (Menu::Search(notARecursiveCall)) {
            case 1:
                while(localSession){
                    if(!notARecursiveCall){
                        arrivalAirports = get_airports_by_city_country();
                        if(departuresAirports.empty()){ localSession = false;
                            return;}
                        return;
                    }else{
                        departuresAirports = get_airports_by_city_country();
                        if(departuresAirports.empty()){ localSession = false;
                            continue;}
                        search_flights_menu(false);
                    }
                }
                break;
            case 2:
                while(localSession){
                    if(!notARecursiveCall){
                        arrivalAirports.push_back(get_airports_by_code());
                        if(departuresAirports.empty()){ localSession = false;
                            return;}
                        return;
                    }else{
                        departuresAirports.push_back(get_airports_by_code());
                        if(departuresAirports.empty()){ localSession = false;
                            continue;}
                        search_flights_menu(false);
                    }
                }
                break;
            case 3:
                while(localSession){
                    if(!notARecursiveCall){
                        arrivalAirports = get_airports_by_coordinates();
                        if(departuresAirports.empty()){ localSession = false;
                            return;}
                        return;
                    }else{
                        departuresAirports = get_airports_by_coordinates();
                        if(departuresAirports.empty()){ localSession = false;
                            continue;}
                        search_flights_menu(false);
                    }
                }
                break;
            case 9:
                localSession = false;
                break;
        }
        if(!departuresAirports.empty() && !arrivalAirports.empty()){
            search_flights(departuresAirports, arrivalAirports);
            departuresAirports.clear();
            arrivalAirports.clear();
        }
    }
}

std::vector<Airport> Manager::get_airports_by_coordinates(){
    localSession = true;
    std::vector<Airport> nearby_airports;
    while(localSession) {
        Utility::header("SkyPlanner");
        Utility::header("Flight Search - Coordinates");
        std::cout << "Enter the latitude: \n-->";
        double latitude;
        std::cin >> latitude;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cout << latitude;

        std::cout << "Enter the longitude: \n-->";
        double longitude;
        std::cin >> longitude;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cout << longitude;
        // Read in the maximum distance to search for airports
        std::cout << "Enter the maximum distance: \n-->";
        double max_distance;
        std::cin >> max_distance;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cout << "Airports within " << max_distance << " kilometers of (" << latitude << ", " << longitude << "):\n";
        localSession = false;
        return flight_network.GetAirportsWithinDistance(latitude,longitude,max_distance);
    }
}

Airport Manager::get_airports_by_code(){
    localSession = true;
    std::string airportCode;
    while(localSession){
        airportCode = Utility::getAirportCode();
        if(airportCode == "exit"){
            localSession = false;
            return {"---"};
        }
        try{Airport airport = airports.at(airportCode);
            localSession = false;
            return airport;
        }catch (std::out_of_range& e){
            std::cout << "It seems like that airport doesn't exist. Try again!\n";
        }

    }
}
std::vector<Airport> Manager::get_airports_by_city_country(){
    localSession = true;
    std::string cityCountryInputStr;
    while(localSession){
        cityCountryInputStr = Utility::getCity();
        if(cityCountryInputStr == "exit"){
            localSession = false;
            return std::vector<Airport>{};
        }
        option =1;
        for(auto const& [citycountry,vec]: cities){
            if(Utility::isSubstring(citycountry, cityCountryInputStr)){
                std::cout  << option << ". " << citycountry << "\n";
                option++;
            }
        }
        if(option < 2){
            std::cerr << "I didn't find any city/country by that name, try again!\n";
            continue;
        }
        std::cout << "-->";
        std::cin >> choice;
        if(choice < 1 || choice >= option || std::cin.bad()){
            std::cerr << "Invalid entry, try again!\n";
            continue;
        }
        option=1;

        for(auto const& [citycountry,vec]: cities){
            if(Utility::isSubstring(citycountry, cityCountryInputStr)){
                if(option == choice){
                    std::cout << "You chose " << citycountry << "\n";
                    localSession = false;
                    return vec;
                }
                option++;
            }
        }

    }
    return std::vector<Airport>{};
}

void Manager::search_flights(std::vector<Airport> departures_airports, std::vector<Airport> arrival_airports){

    std::vector<Flight> route;
    Utility::clear_screen();
    Utility::header("SkyPlanner");
    Utility::body("This is one of the shortest possible routes",{""});
    std::cout << "FROM:\n" << departures_airports.front().getCity() << ", " << departures_airports.front().getCountry() << "\n";
    for(const auto& air: departures_airports){
        std::cout << air.getName() << "- " << air.getCode() << "\n";
    }
    std::cout << "TO:\n";
    std::cout << arrival_airports.front().getCity() << ", " << arrival_airports.front().getCountry() << "\n";
    for(const auto& air: arrival_airports){
        std::cout << air.getName() << "- " << air.getCode() << "\n";
    }
    std::cout << "\n";
     int i;

    for(auto const& depAir: departures_airports) {
        for (auto const &arrAir: arrival_airports) { //TODO
            route = flight_network.FindShortestRoute(depAir, arrAir);
            for (const auto &flight: route) {
                    std::cout << flight.getDeparture() << " -> " << flight.getArrival() << " (" << flight.getAirline()
                              << ") - " << airlines.at(flight.getAirline()).getName() << std::endl;
            }
        }
        std::cout << "\n";
    }
    Utility::body("",{"1. Show detailed route information","2. Show all routes with the same amount of flights","3. Search for a route using one airline"});
    Utility::footer();
    std::cout << "-->";
    std::cin >> i;
    switch (i) {
        case 1:
            show_flight_info(departures_airports,arrival_airports);
            break;
        case 2:
            show_multiple_routes(departures_airports, arrival_airports);
            break;
        case 3:
            search_one_airline(departures_airports,arrival_airports);
            break;
        case 9:
            return;
    }
}
void Manager::show_multiple_routes(const std::vector<Airport>& departures_airports, const std::vector<Airport>& arrival_airports){
    Utility::clear_screen();
    std::vector<std::vector<Flight>> routes;
    double distance = 0;
    int i = 1, option;
    Utility::header("SkyPlanner");
    Utility::body("Routes with the same number of flights",{"this may take a few seconds"});

    // ---

    for(auto const& depAir: departures_airports) {
        for (auto const &arrAir: arrival_airports) { //TODO
            routes = flight_network.FindShortestRoutes(depAir, arrAir);
            for (const auto &route: routes) {
                std::cout << "Option :" << i << "\n";
                distance = 0;
                for(const auto &flight : route){
                    std::cout << flight.getDeparture() << " -> " << flight.getArrival() << " (" << flight.getAirline()
                              << ") - " << airlines.at(flight.getAirline()).getName() << std::endl;

                }
                i++;
                std::cout << "\n";
            }
        }
        std::cout << "\n";
    }
    Utility::body("Choose a flight to show detailed info about it",{""});
    Utility::footer();
    std::cout << "-->";
    std::cin >> option;
    if(option == 9)return; // todo: serious bug -- option 9 coincides with back
    i = 1;
    for(auto const& depAir: departures_airports) {
        for (auto const &arrAir: arrival_airports) { //TODO
            routes = flight_network.FindShortestRoutes(depAir, arrAir);
            for (const auto &route: routes) {
                if(i == option){
                    show_flight_info(departures_airports,arrival_airports);
                    return;
                }
                i++;
            }
        }
    }

    // ---


}
void Manager::search_one_airline(const std::vector<Airport> &departures_airports,const std::vector<Airport> &arrival_airports) {
    localSession = true;
    std::string airlineCode;
    std::vector<std::vector<Flight>> routes;
    while(localSession){
        Utility::clear_screen();
        Utility::header("SkyPlanner");
        Utility::body("Routes with one airline",{""});
        airlineCode = Utility::getAirportCode();
        if(airlineCode == "exit"){
            localSession = false;
            return;
        }
        try{
            Airline airline = airlines.at(airlineCode);
            int i = 1;
            for(auto const& depAir: departures_airports) {
                for (auto const &arrAir: arrival_airports) { //TODO
                    routes = flight_network.GetPathsWithOneAirline(depAir,arrAir,airlineCode);
                    if(routes.empty())std::cout << "No routes found!" << "\n";
                    for (const auto &route: routes) {
                        std::cout << "Option :" << i << "\n";
                        for(const auto &flight : route){
                            std::cout << flight.getDeparture() << " -> " << flight.getArrival() << " (" << flight.getAirline()
                                      << ") - " << airlines.at(flight.getAirline()).getName() << std::endl;

                        }
                        i++;
                        std::cout << "\n";
                    }
                }
                std::cout << "\n";
                Utility::body("Choose a flight to show detailed info about it",{""});
                Utility::footer();
                std::cout << "-->";
                std::cin >> option;
                if(option == 9)return; // todo: serious bug -- option 9 coincides with back
                i = 1;
                for(auto const& depAir: departures_airports) {
                    for (auto const &arrAir: arrival_airports) { //TODO
                        routes = flight_network.FindShortestRoutes(depAir, arrAir);
                        for (const auto &route: routes) {
                            if(i == option){
                                show_flight_info(departures_airports,arrival_airports);
                                return;
                            }
                            i++;
                        }
                    }
                }
            }
            return;
        }catch (std::out_of_range& e){
            std::cout << "It seems like that airline doesn't exist. Try again!\n";
        }

    }
}
void Manager::show_flight_info(const std::vector<Airport>& departures_airports, const std::vector<Airport>& arrival_airports) {
    Utility::clear_screen();
    std::vector<Flight> newroute;
    int i = 1;
    int countair = 0;
    Utility::header("SkyPlanner");
    Utility::body("Route Information", {  "("+  departures_airports.front().getCountry()  + ") " +departures_airports.front().getCity() + " ---> " + arrival_airports.front().getCity() + " (" + arrival_airports.front().getCountry() +")", ""});

    for (auto const& depAir : departures_airports) {
        if(departures_airports.size()!=1){
            std::cout << "FROM: " << depAir.getName() << " Airport\n";
        }
        i = 1;
        for (auto const& arrAir : arrival_airports) {
            if(arrival_airports.size()!=1){
                std::cout << "TO: " << arrAir.getName() << " Airport\n";
            }
            std::cout << "------------------------------------------------------------------------------------------------------------------|\n";
            std::cout << "Flight #    |        Departure Airport      |        Arrival Airport        |                Airline              |\n";
            std::cout << "------------|-------------------------------|-------------------------------|-------------------------------------|\n";
            newroute = flight_network.FindShortestRoute(depAir, arrAir);
            if (countair != 0) i = 1;
            for (const auto& flight : newroute) {
                std::cout << std::setw(11) << i << " | ";
                // Print departure airport information
                std::cout << std::setw(29) << airports.at(flight.getDeparture()).getCity() + " (" +
                        airports.at(flight.getDeparture()).getCode() + ")";
                std::cout << " | ";

                // Print arrival airport information
                std::cout << std::setw(29) << airports.at(flight.getArrival()).getCity() + " (" +
                        airports.at(flight.getArrival()).getCode() + ")";
                std::cout << " | ";

                // Print airline information
                std::cout << std::setw(35) << airlines.at(flight.getAirline()).getName();
                std::cout << " | ";

                if (airports.at(flight.getArrival()).getCountry() != arrival_airports.back().getCountry()) {
                    std::cout << std::setw(35) << " (Connecting flight in " + airports.at(flight.getArrival()).getCountry() + ")\n";
                } else {
                    std::cout << "\n";
                }
                i++;
            }
            countair++;
            std::cout << "\n";
        }
        std::cout << "\n";
    }
    Utility::footer();
    std::cout << "-->";
    std::cin >> i;
}

bool Manager::loadData(const std::string& fname1, const std::string& fname2, const std::string& fname3) {
    std::cout << "loading data...\n";
    std::vector<Airline> airlinesVEC = Utility::loadDataFromCSV<Airline>(fname1);
    std::vector<Airport> airportsVEC = Utility::loadDataFromCSV<Airport>(fname2);
    std::vector<Flight> flightsVEC = Utility::loadDataFromCSV<Flight>(fname3);

    for(const auto& airline: airlinesVEC){
        airlines.emplace(airline.getCode(),airline);
    }

    for(const auto& airport: airportsVEC){
        airports.emplace(airport.getCode(), airport);
        cities[airport.getCity() + ", " + airport.getCountry()].push_back(airport);
        flight_network.addAirport(airport);
    }
    for(const auto& flight: flightsVEC){
        flight_network.addFlight(flight);
    }

    airlinesVEC.clear();
    airportsVEC.clear();
    flightsVEC.clear();


    if(airlines.size() > 342 && airports.size() > 3000){
        return true;
    }else{
        std::cerr << "There was an error loading the data, make sure the files are complete and in the src/dataset/ directory.\nThe executable must be in the cmake-build-debug directory.\n";
        return false;
    }

}



void Manager::testing() {
    Graph graph;
    std::unordered_map<std::string,Airport> airports;

    Airport airport1("CGD","Charles de Gaulle","Paris","France",1.0,1.0);
    Airport airport2("JFK","John F Kennedy","New York","United States",1.0,1.0);

    Flight cgd_jfk("CGD","JFK","AAL");

    graph.addAirport(airport1);
    graph.addAirport(airport2);

    airports.emplace(airport1.getCode(), airport1);
    airports.emplace(airport2.getCode(), airport2);

    graph.addFlight(cgd_jfk);

    std::vector<std::vector<Flight>>  route = graph.FindShortestRoutes(airport1, airport2);
    std::cout << "Shortest route from Lisbon to London:" << std::endl;
    int i =1;
    for (const auto& options : route) {
        std::cout << "Option " << i << ":\n";
        for(const auto& flight: options){
            std::cout << flight.getDeparture() << " -> " << flight.getArrival()<< " (" << flight.getAirline() << ")" << std::endl;
            std::cout <<  airports.at(flight.getDeparture()).getName() << " -> " << airports.at(flight.getArrival()).getName()<< std::endl;
        }
        i++;
    }



/*
    // Add some airports to the graph
    Airport lisbon{"Lisbon", 38.736946, -9.142685};
    Airport paris{"Paris", 48.856614, 2.352222};
    Airport london{"London", 51.507351, -0.127758};
    Airport porto{"Porto", 51.507351, -0.127758};
    Airport aveiro{"Aveiro", 51.507351, -0.127758};
    graph.AddAirport(lisbon);
    graph.AddAirport(paris);
    graph.addAirport(london);

    // Add some flights to the graph
    Flight lisbon_paris;
    lisbon_paris.airline = "TAP";
    lisbon_paris.arrival = &paris;
    lisbon_paris.departure = &lisbon;

    Flight paris_london;
    paris_london.airline = "Air France";
    paris_london.departure = &paris;
    paris_london.arrival = &london;


    Flight lisbon_london;
    lisbon_london.airline = "British Airways";
    lisbon_london.departure = &lisbon;
    lisbon_london.arrival = &london;

    Flight lisbon_porto;
    lisbon_porto.airline = "TAP";
    lisbon_porto.departure = &lisbon;
    lisbon_porto.arrival = &porto;
    Flight porto_london;
    porto_london.airline = "TAP";
    porto_london.departure = &porto;
    porto_london.arrival = &london;


    graph.AddFlight(lisbon_paris);
    graph.AddFlight(paris_london);
    graph.AddFlight(lisbon_london);
    graph.AddFlight(lisbon_porto);
    graph.addFlight(porto_london);

    // Find the shortest route from Lisbon to London
    std::vector<std::vector<Flight>>  route = graph.FindShortestRoutes(lisbon, london);
    std::cout << "Shortest route from Lisbon to London:" << std::endl;
    int i =1;
    for (const auto& options : route) {
        std::cout << "Option " << i << ":\n";
        for(const auto& flight: options){
            std::cout << flight.departure->name << " -> " << flight.arrival->name << " (" << flight.airline << ")" << std::endl;
        }
        i++;
    }
    i =1;
    std::cout << "\nAll possible flights from Lisbon to London using TAP:" << std::endl;
    std::vector<std::vector<Flight>> flig = graph.GetPathsWithOneAirline(lisbon,london,"TAP");
    for (const auto& options : flig) {
        std::cout << "Option " << i << ":\n";
        for(const auto& flight: options){
            std::cout << flight.departure->name << " -> " << flight.arrival->name << " (" << flight.airline << ")" << std::endl;
        }
        i++;
    }

    // Get the number of flights from Lisbon
    //int num_flights = graph.getNumFlightsFromAirport(lisbon);
    //std::cout << "Number of flights from Lisbon: " << num_flights << std::endl;

    Get the number of different airlines that operate flights from Lisbon
    int num_airlines = graph.GetNumAirlinesFromAirport(lisbon);
    std::cout << "Number of different airlines that operate flights from Lisbon: " << num_airlines << std::endl;
*/
}



/*for(auto const& depAir: departures_airports){
        for(auto const& arrAir: arrival_airports){
            route = flight_network.FindShortestRoutes(depAir, arrAir);
            int i =1;
            for (const auto& options : route) {
                std::cout << "\nOption " << i << ":\n";
                for(const auto& flight: options){
                    std::cout << flight.getDeparture() << " -> " << flight.getArrival()<< " (" << flight.getAirline() << ") - " << airlines.at(flight.getAirline()).getName() << std::endl;
                }
                i++;
            }

        }
    }*/