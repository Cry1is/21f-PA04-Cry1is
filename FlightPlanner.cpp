//
// Created by Zachary on 11/1/2021.
//

#include "FlightPlanner.h"

// variable info, statuses, errors
bool* errorLevels = new bool[3]{false, false, false};

FlightPlanner::FlightPlanner() {
    this->flightDataFile = "";
    this->itineraryFile = "";
    this->cost = 0;
    this->time = 0;
}

FlightPlanner::FlightPlanner(string flightDataFile, string itineraryFile) {
    this->flightDataFile = flightDataFile;
    this->itineraryFile = itineraryFile;
    this->cost = 0;
    this->time = 0;
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
        while(!tempCost.isEmpty())
            tempCost.pop();
        while(!tempTime.isEmpty())
            tempTime.pop();
        getItineraries(start, end, type);
    }
}

void FlightPlanner::getItineraries(string start, string end, string type) {
    // linked list of linked lists to return
    DSLinkedList<DSLinkedList<string>> itineraries;

    while(!stack.isEmpty())
        stack.pop();

    stack.push(start);
    int tempCost1 = 0;
    int tempTime1 = 0;
    tempCost.push(tempCost1);
    tempTime.push(tempTime1);

    while (!stack.isEmpty()) {
        // find the city in the flights linked list
        OriginCity *temp = new OriginCity(stack.peek());
        if (!flights.contains(*temp))
            throw std::out_of_range("city does not exist");
        OriginCity* curCity = &flights.find(*temp)->data;
        delete temp;

        if (curCity->isEnd()) {
            if (stack.peek() == end) {
                if (errorLevels[1])
                    cout << "found a path" << endl;
                itineraries.push_back(stack.getList());
            }

            cost -= tempCost.peek();
            time -= tempTime.peek();

            tempCost.pop();
            tempTime.pop();

            curCity->resetPaths();
            stack.pop();
            if (errorLevels[0])
                cout << stack.getList() << ", " << cost << ", " << time <<endl;
        }
        else {
            if (!isVisited(curCity->getCur().getName())) {
                string name = curCity->getCur().getName();

                int tempCost1 = curCity->getCur().getCost();
                tempCost.push(tempCost1);
                int tempTime1 = curCity->getCur().getTime();
                tempTime.push(tempTime1);

                cost += tempCost.peek();
                time += tempTime.peek();
                stack.push(name);
                if (errorLevels[0])
                    cout << stack.getList() << ", " << cost << ", " << time <<endl;
            }
            curCity->movePaths();
        }
    }
}

bool FlightPlanner::isVisited(string city) {
    DSStack<string> tempStack;
    while (!stack.isEmpty()) {
        if (errorLevels[1])
            cout << stack.peek() << endl;
        if (city == stack.peek()) {
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