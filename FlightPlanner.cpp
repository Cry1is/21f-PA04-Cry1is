//
// Created by Zachary on 11/1/2021.
//

#include "FlightPlanner.h"

// variable info, statuses, errors
bool* errorLevels = new bool[3]{true, true, false};

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
        DSLinkedList<DSLinkedList<string>> itineraries = getItineraries(start, end, type);
        cout << itineraries;
    }
}

DSLinkedList<DSLinkedList<string>> FlightPlanner::getItineraries(string start, string end, string type) {
    // open the itinerary file
    ifstream in(itineraryFile);

    // linked list of linked lists to return
    DSLinkedList<DSLinkedList<string>> itineraries;

    DSStack<string> stack;

    stack.push(start);

    while (!stack.isEmpty()) {
        // find the city in the flights linked list
        OriginCity *temp = new OriginCity(stack.peek());
        if (!flights.contains(*temp))
            throw std::out_of_range("city does not exist");
        OriginCity* curCity = &flights.find(*temp)->data;
        delete temp;

        if (curCity->isEnd()) {
            if (stack.peek() == end) {
                DSLinkedList<string> temp = stack.getList();
                cout << temp << endl;
                cout << stack.getList().getTail()->data << endl;
            }

            curCity->resetPaths();

            stack.pop();
        }
        else {
            if (!isVisited(curCity->getCur().getName(), stack))
                stack.push(curCity->getCur().getName());
            curCity->movePaths();
        }
    }
    return itineraries;
}
/*
DSLinkedList<DSLinkedList<string>> FlightPlanner::getItineraries(string start, string end, string type) {
    // open the itinerary file
    ifstream in(itineraryFile);

    // linked list of linked lists to return
    DSLinkedList<DSLinkedList<string>> itineraries;

    DSStack<string> stack;

    stack.push(start);

    while (!stack.isEmpty()) {
        if (errorLevels[1])
            cout << "check if stack top " << stack.peek() << " is destination" << endl;
        if (stack.peek() == end) {
            if (errorLevels[1])
                cout << "stack top is destination" << endl;
            DSLinkedList<string> temp = stack.getList();
            itineraries.push_back(temp);
            stack.pop();
        }
        else {
            if (errorLevels[1])
                cout << "stack top is not destination" << endl;
            // find the city in the flights linked list
            OriginCity *temp = new OriginCity(stack.peek());
            if (!flights.contains(*temp))
                throw std::out_of_range("city does not exist");
            OriginCity curCity = flights.find(*temp)->data;
            delete temp;

            if (errorLevels[1])
                cout << "for connection in stack top" << endl;
            DSLinkedList<DestinationCity> *connection = &curCity.getPaths();
            if (connection->getItr() == nullptr) {
                if (errorLevels[1])
                    cout << "no more connections" << endl;
                connection->resetItr();
                stack.pop();
                continue;
            }
            bool exit = false;
            while (connection->getItr() != nullptr && !exit) {
                if (errorLevels[1])
                    cout << "check if the connection " << connection->getItr()->data.getName() << " is on the stack" << endl;
                if (isVisited(connection->getItr()->data.getName(), stack)) {
                    if (errorLevels[1])
                        cout << "connection is on the stack, continue" << endl;
                    connection->moveItr();
                }
                else {
                    if (errorLevels[1])
                        cout << "connection is not on the stack" << endl;
                    stack.push(connection->getItr()->data.getName());
                    connection->moveItr();
                    exit = true;
                }
            }
            if (!exit)
                stack.pop();
        }
    }

    return itineraries;
}*/

bool FlightPlanner::isVisited(string city, DSStack<string> stack) {
    while (!stack.isEmpty()) {
        /*if (errorLevels[1])
            cout << stack.peek() << endl;*/
        if (city == stack.peek())
            return true;
        stack.pop();
    }
    return false;
}