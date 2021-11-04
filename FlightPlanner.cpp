//
// Created by Zachary on 11/1/2021.
//

#include "FlightPlanner.h"

// variable info, statuses, errors
bool* errorLevels = new bool[3]{false, false, false};

FlightPlanner::FlightPlanner() {
    this->flightDataFile = "";
    this->itineraryFile = "";
}

FlightPlanner::FlightPlanner(string flightDataFile, string itineraryFile) {
    this->flightDataFile = flightDataFile;
    this->itineraryFile = itineraryFile;
}

void FlightPlanner::setFiles(string flightDataFile, string itineraryFile) {
    this->flightDataFile = flightDataFile;
    this->itineraryFile = itineraryFile;
}

void FlightPlanner::setFlightData() {
    // open the flightData file
    ifstream in(flightDataFile);

    // temporary char array to read from file
    char* temp = new char[1024];

    // get the number of flights
    int count;
    in >> count;
    in.getline(temp, 1024);

    if (errorLevels[0])
        cout << "count: " << count << endl;

    // record all the flights in the flights linked list
    for (int i = 0; i < count; i++) {
        // read a line
        in.getline(temp, 1024);
        stringstream s(temp);

        // variables
        string origin, dest, airline;
        int cost, time;

        // pass the line data to the variables
        s >> origin >> dest >> cost >> time >> airline;

        if (errorLevels[0])
            cout << origin << "," << dest << "," << cost << "," << time << "," << airline << endl;

        if (errorLevels[1])
            cout << "creating the 2 origin and 2 destination cities" << endl;
        // create the origin and destination cities
        OriginCity* o = new OriginCity(origin);
        OriginCity* o2 = new OriginCity(dest);
        DestinationCity* d = new DestinationCity(dest, cost, time, airline);
        DestinationCity* d2 = new DestinationCity(origin, cost, time, airline);

        OriginCity* temp = nullptr,* temp2 = nullptr;

        if (errorLevels[1])
            cout << "pushing the 2 origin cities to the flights list if they don't exist" << endl;
        // check for the origin city in the list, if it doesn't exist, push it to the list
        if (!flights.contains(*o))
            flights.push_back(*o);
        else
            temp = o;
        if (!flights.contains(*o2))
            flights.push_back(*o2);
        else
            temp2 = o2;

        if (errorLevels[1])
            cout << "getting the origin cities from flights and pushing the corresponding destination cities to their list" << endl;
        // grab the origin city from the list and add the destination city to its path
        o = &flights.find(*o)->data;
        o->addPath(*d);
        o2 = &flights.find(*o2)->data;
        o2->addPath(*d2);

        if (errorLevels[1])
            cout << "deleting the temporarily created cities if they aren't needed" << endl;
        // delete the temporary cities if they already exist in the list
        if (temp != nullptr)
            delete temp;
        if (temp2 != nullptr)
            delete temp2;
    }

    if (errorLevels[0]) {
        cout << "trying to print out the flights" << endl;
        flights.resetItr();
        while (flights.getItr() != nullptr) {
            cout << flights.getItr()->data << ": ";
            cout << flights.getItr()->data.getPaths() << endl;
            flights.moveItr();
        }
    }
}

void FlightPlanner::getFlights() {
    // open the itinerary file
    ifstream in(itineraryFile);

    // temporary char array to read from file
    char* temp = new char[1024];

    // get the number of itineraries
    int count;
    in >> count;
    in.getline(temp, 1024);

    if (errorLevels[0])
        cout << "count: " << count << endl;

    // record all of the itineraries
    for (int i = 0; i < count; i++) {
        // read a line
        in.getline(temp, 1024);
        stringstream s(temp);

        // variables
        string start, end, type;

        // pass the line data to the variables
        s >> start >> end >> type;

        if (errorLevels[0])
            cout << start << ", " << end << ", " << type << endl;

        // get the itineraries of the given path
        DSLinkedList<DSStack<DestinationCity>> itineraries = getItineraries(start, end, type);
        itineraries.resetItr();
        int j = 1;
        while (itineraries.getItr() != nullptr) {
            cout << "Itinerary " << j << ": " << endl;
            outputPath(itineraries.getItr()->data);
            itineraries.moveItr();
            j++;
        }
    }
}

DSLinkedList<DSStack<DestinationCity>> FlightPlanner::getItineraries(string start, string end, string type) {
    // linked list of linked lists to return
    DSLinkedList<DSStack<DestinationCity>> itineraries;

    while(!stack.isEmpty())
        stack.pop();

    DestinationCity startCity(start, 0, 0, "");
    stack.push(startCity);

    while (!stack.isEmpty()) {
        // find the city in the flights linked list
        OriginCity *temp = new OriginCity(stack.peek().getName());
        if (!flights.contains(*temp))
            throw std::out_of_range("city does not exist");
        OriginCity* curCity = &flights.find(*temp)->data;
        delete temp;

        if (curCity->isEnd()) {
            if (stack.peek().getName() == end) {
                if (errorLevels[0]) {
                    cout << "found a path" << endl;
                    outputPath(stack);
                }
                itineraries.push_back(stack);
            }
            curCity->resetPaths();
            stack.pop();
            if (errorLevels[1])
                cout << stack << endl;
        }
        else {
            if (!isVisited(curCity->getCur())) {
                stack.push(curCity->getCur());
                if (errorLevels[1])
                    cout << stack << endl;
            }
            curCity->movePaths();
        }
    }
    return itineraries;
}

bool FlightPlanner::isVisited(DestinationCity city) {
    DSStack<DestinationCity> tempStack;
    while (!stack.isEmpty()) {
        if (city.getName() == stack.peek().getName()) {
            while (!tempStack.isEmpty()) {
                stack.push(tempStack.peek());
                tempStack.pop();
            }
            return true;
        }
        tempStack.push(stack.peek());
        stack.pop();
    }
    while (!tempStack.isEmpty()) {
        stack.push(tempStack.peek());
        tempStack.pop();
    }
    return false;
}

void FlightPlanner::outputPath(DSStack<DestinationCity>& s) {
    DSStack<DestinationCity> tempStack;
    int count = 0, time = 0;
    double cost = 0;
    while (!s.isEmpty()) {
        tempStack.push(s.peek());
        s.pop();
    }

    string origin = tempStack.peek().getName();
    while (!tempStack.isEmpty()) {
        s.push(tempStack.peek());
        tempStack.pop();
        if (tempStack.isEmpty())
            continue;
        cout << origin << " -> ";
        cout << tempStack.peek().getName() << " (";
        cout << tempStack.peek().getAirline() << ")" << endl;
        origin = tempStack.peek().getName();
        count++;
        time += tempStack.peek().getTime();
        cost += tempStack.peek().getCost();
    }
    cout << "Totals for Itinerary: Time: " << time << " Cost: " << cost << endl;
}