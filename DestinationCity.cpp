//
// Created by Zachary on 11/1/2021.
//

#include "DestinationCity.h"

DestinationCity::DestinationCity() {
    this->name = "";
    this->cost = 0;
    this->time = 0;
    this->airline = "";
}

DestinationCity::DestinationCity(string name, int cost, int time, string airline) {
    this->name = name;
    this->cost = cost;
    this->time = time;
    this->airline = airline;
}

void DestinationCity::setName(string name) {
    this->name = name;
}

string DestinationCity::getName() {
    return this->name;
}

void DestinationCity::setCost(int cost) {
    this->cost = cost;
}

int DestinationCity::getCost() {
    return this->cost;
}

void DestinationCity::setAirline(string airline) {
    this->airline = airline;
}

string DestinationCity::getAirline() {
    return this->airline;
}

bool DestinationCity::operator==(DestinationCity& other) {
    return this->name == other.getName() && this->airline == other.getAirline();
}

std::ostream& operator<<(std::ostream& fout, const DestinationCity& d) {
    fout << d.name << "," << d.cost << "," << d.time << "," << d.airline;
    return fout;
}
