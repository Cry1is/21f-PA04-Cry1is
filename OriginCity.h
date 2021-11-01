//
// Created by Zachary on 11/1/2021.
//

#ifndef INC_21F_FLIGHT_PLANNER_ORIGINCITY_H
#define INC_21F_FLIGHT_PLANNER_ORIGINCITY_H

#include "DSLinkedList.h"
#include "DestinationCity.h"

class OriginCity {
private:
    string name;
    DSLinkedList<DestinationCity> paths;
public:
    OriginCity();
    OriginCity(string name);

    void setName(string);
    string getName();

    void setPaths(DSLinkedList<DestinationCity>&);
    DSLinkedList<DestinationCity>& getPaths();

    void addPath(DestinationCity&);
    void movePaths();
    void resetPaths();
    DestinationCity& getCur();
    bool isEnd();

    bool operator==(OriginCity&);
    friend std::ostream& operator<<(std::ostream&, const OriginCity&);
};

#endif //INC_21F_FLIGHT_PLANNER_ORIGINCITY_H
