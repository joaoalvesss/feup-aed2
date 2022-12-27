cmake_minimum_required(VERSION 3.23)
project(Projeto_AED_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Projeto_AED_2 main.cpp src/utils.h src/graph.h src/airport.h src/airline.h src/menu.h src/flight.h src/airline.cpp src/airport.cpp src/flight.cpp src/graph.cpp src/menu.cpp src/utils.cpp src/Manager.cpp src/Manager.h)
