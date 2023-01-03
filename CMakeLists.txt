cmake_minimum_required(VERSION 3.24)
project(feup_aed2)

set(CMAKE_CXX_STANDARD 17)

add_executable(feup_aed2 main.cpp src/Manager.cpp src/Manager.h src/Graph.cpp src/Graph.h src/Airport.cpp src/Airport.h src/Airlines.cpp src/Airlines.h src/Flight.cpp src/Flight.h src/Utility.cpp src/Utility.h src/Menu.cpp src/Menu.h)
