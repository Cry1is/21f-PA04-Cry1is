/**
 * Fall 2021 PA 04 - Flight Planner Template Repo.
 * Based on PA 02 Template repo
 */

#include <iostream>
#include <fstream>

/**
 * catch_setup.h and catch_setup.cpp contain the #define directive for
 * the CATCH2 framework.  You can see in main below how I'm calling the
 * runCatchTests() function which is declared in this header.
 *
 * On average, this should reduce the build time for your project on your local
 * machine.
 */

#include "FlightPlanner.h"

int main(int argc, char** argv) {
    if(argc == 1) {
        std::cout << "no files found" << std::endl;
        return 1;
    }
    FlightPlanner* f = new FlightPlanner(argv[1], argv[2], argv[3]);
    f->setFlightData();
    f->getFlights();

    delete f;

    return 0;
}