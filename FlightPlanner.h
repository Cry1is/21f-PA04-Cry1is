//
// Created by Zachary on 11/1/2021.
//

#ifndef INC_21F_FLIGHT_PLANNER_FLIGHTPLANNER_H
#define INC_21F_FLIGHT_PLANNER_FLIGHTPLANNER_H

#include <fstream>
#include <sstream>
#include "OriginCity.h"
#include "DSStack.h"

class FlightPlanner {
private:
    DSLinkedList<OriginCity> flights;
    string flightDataFile, itineraryFile;
public:
    FlightPlanner();

    FlightPlanner(string, string);

    void setFiles(string, string);

    void setFlightData();

    void getFlights();

    DSLinkedList<DSLinkedList<string>> getItineraries(string, string, string);

    bool isVisited(string, DSStack<string>);
};

#endif //INC_21F_FLIGHT_PLANNER_FLIGHTPLANNER_H
