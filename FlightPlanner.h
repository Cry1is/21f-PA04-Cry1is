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
    DSStack<DestinationCity> stack;
    string flightDataFile, itineraryFile, outputFile;
public:
    FlightPlanner();

    FlightPlanner(string, string, string);

    void setFiles(string, string, string);

    void setFlightData();

    void getFlights();

    DSLinkedList<DSStack<DestinationCity>> getItineraries(string, string);

    bool isVisited(DestinationCity);

    int* calcPath(DSStack<DestinationCity>&);
    int* writePath(DSStack<DestinationCity>&, ofstream&);

    void status(string, int indent = 2);
    void warning(string, int indent = 4);
    void error(string, int indent = 6);
};

#endif //INC_21F_FLIGHT_PLANNER_FLIGHTPLANNER_H
