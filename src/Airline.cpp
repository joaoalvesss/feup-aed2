#include "../headers/Airline.h"

#include <utility>
#include <iostream>
#include "../headers/Utils.h"

Airline::Airline(string code, string name, string callsign, string country) {
    this->code = std::move(code);
    this->name = std::move(name);
    this->callsign = std::move(callsign);
    this->country = std::move(country);
}

void Airline::print(){
    cout << this->code << " " << this->name << " " << this->callsign << " " << this->country;
}