cmake_minimum_required(VERSION 3.23)
project(Projeto_AED_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Projeto_AED_2 main.cpp headers/Utils.h headers/Graph.h headers/Airline.h headers/Menu.h headers/Flight.h src/Airline.cpp src/Flight.cpp src/Graph.cpp src/Menu.cpp src/Utils.cpp src/Manager.cpp headers/Manager.h src/Airport.cpp headers/Airport.h)
