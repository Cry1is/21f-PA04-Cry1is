//
// Created by Zachary on 11/1/2021.
//

#ifndef INC_21F_FLIGHT_PLANNER_DESTINATIONCITY_H
#define INC_21F_FLIGHT_PLANNER_DESTINATIONCITY_H

#include <iostream>

using namespace std;

class DestinationCity {
private:
    string name, airline;
    int cost, time;
public:
    DestinationCity();
    DestinationCity(string, int, int, string);

    void setName(string);
    string getName();

    void setCost(int);
    int getCost();

    void setTime(int);
    int getTime();

    void setAirline(string);
    string getAirline();

    bool operator==(DestinationCity&);
    friend std::ostream& operator<<(std::ostream&, const DestinationCity&);
};

#endif //INC_21F_FLIGHT_PLANNER_DESTINATIONCITY_H
