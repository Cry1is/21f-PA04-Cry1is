//
// Created by Zachary on 11/1/2021.
//

#include "FlightPlanner.h"

// statuses, warnings, errors
bool* errorLevels = new bool[3]{false, false, false};

FlightPlanner::FlightPlanner() {
    this->flightDataFile = "";
    this->itineraryFile = "";
}

FlightPlanner::FlightPlanner(string flightDataFile, string itineraryFile, string outputFile) {
    this->flightDataFile = flightDataFile;
    this->itineraryFile = itineraryFile;
    this->outputFile = outputFile;
}

void FlightPlanner::setFiles(string flightDataFile, string itineraryFile, string outputFile) {
    this->flightDataFile = flightDataFile;
    this->itineraryFile = itineraryFile;
    this->outputFile = outputFile;
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

    status("Number of flights: " + to_string(count));

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

        if (origin.empty() || dest.empty() || airline.empty())
            warning("Some fields may be empty");

        // create the origin and destination cities
        OriginCity* o = new OriginCity(origin);
        OriginCity* o2 = new OriginCity(dest);
        DestinationCity* d = new DestinationCity(dest, cost, time, airline);
        DestinationCity* d2 = new DestinationCity(origin, cost, time, airline);

        status("Created the origin and destination cities for a flight");

        OriginCity* temp = nullptr,* temp2 = nullptr;

        // check for the origin city in the list, if it doesn't exist, push it to the list
        if (!flights.contains(*o))
            {flights.push_back(*o); status("new origin city " + o->getName() + " inserted");}
        else
            {temp = o; status("origin city " + o->getName() + " exists");}
        if (!flights.contains(*o2))
            {flights.push_back(*o2); status("new origin city " + o2->getName() + " inserted");}
        else
            {temp2 = o2; status("origin city " + o2->getName() + " exists");}

        // grab the origin city from the list and add the destination city to its path
        o = &flights.find(*o)->data;
        o->addPath(*d); status("destination city " + d->getName() + " added to " + o->getName());
        o2 = &flights.find(*o2)->data;
        o2->addPath(*d2); status("destination city " + d2->getName() + " added to " + o2->getName());

        // delete the temporary cities if they already exist in the list
        if (temp != nullptr)
            delete temp;
        if (temp2 != nullptr)
            delete temp2;
    }
}

void FlightPlanner::getFlights() {
    // open the itinerary file
    ifstream in(itineraryFile);
    ofstream out(outputFile);

    // temporary char array to read from file
    char* temp = new char[1024];

    // get the number of itineraries
    int count;
    in >> count;
    in.getline(temp, 1024);

    status("Number of itineraries: " + to_string(count));

    // record all of the itineraries
    for (int i = 0; i < count; i++) {
        // read a line
        in.getline(temp, 1024);
        stringstream s(temp);

        // variables
        string start, end, type;

        // pass the line data to the variables
        s >> start >> end >> type;

        status("Starting Location: " + start + "\nEnding Location: " + end + "\nComparison Type: " + type, 0);

        out << "Flight " << i+1 << ": " << start << ", " << end << ", " << type << endl;
        //cout << "Flight " << i+1 << ": " << start << ", " << end << ", " << type << endl;

        // get the itineraries of the given start and end
        DSLinkedList<DSStack<DestinationCity>> itineraries = getItineraries(start, end);

        // counter variable for the itinerary number
        int j = 1;

        // assigning the initial temporary stack that might be printed
        DSStack<DestinationCity> temp = itineraries.getHead()->data;

        // looping through until all itineraries have been printed
        while (!itineraries.isEmpty() && j < 4) {
            out << "  Itinerary " << j << ": " << endl;
            //cout << "  Itinerary " << j << ": " << endl;

            // time and cost current minimum values
            int* min = new int[2]{INT_MAX, INT_MAX};

            // loop through the list to find the current smallest cost and/or time
            itineraries.resetItr();
            while (itineraries.getItr() != nullptr) {
                // get the cost and time of a particular itinerary
                int* value = calcPath(itineraries.getItr()->data);
                status("Minimum Time: " + to_string(min[0]) + " Minimum Cost: " + to_string(min[1]));
                status("Path Time: " + to_string(value[0]) + " Path Cost: " + to_string(value[1]));

                // determine whether the current itinerary is cheaper based on time or cost
                bool lessThan;
                if (type == "T")
                    lessThan = value[0] < min[0] || (value[1] < min[1] && value[0] == min[0]);
                else if (type == "C")
                    lessThan = value[1] < min[1] || (value[0] < min[0] && value[1] == min[1]);

                // if it is cheaper, set temp to its value and adjust min accordingly
                if (lessThan) {
                    status("Path is cheaper than minimum based on " + type, 4);
                    temp = itineraries.getItr()->data;
                    min = value;
                }
                itineraries.moveItr();
            }

            // remove the itinerary that will be printed from the list
            itineraries.remove(temp);

            // print the itinerary
            int* results = writePath(temp, out);
            out << "    Totals for Itinerary " << j << ": Time: " << results[0] << " Cost: " << results[1] << endl;
            //cout << "    Totals for Itinerary " << j << ": Time: " << results[0] << " Cost: " << results[1] << endl;
            j++;
        }
    }

    // close input and output files
    in.close();
    out.close();
}

DSLinkedList<DSStack<DestinationCity>> FlightPlanner::getItineraries(string start, string end) {
    // linked list of linked lists to return
    DSLinkedList<DSStack<DestinationCity>> itineraries;

    while(!stack.isEmpty())
        stack.pop();

    DestinationCity startCity(start, 0, 0, "");
    stack.push(startCity);

    while (!stack.isEmpty()) {
        // find the city in the flights linked list
        OriginCity* temp = new OriginCity(stack.peek().getName());
        if (!flights.contains(*temp)) {
            error("City " + temp->getName() + " does not exist");
            exit(1);
        }
        OriginCity* curCity = &flights.find(*temp)->data;
        delete temp;

        status("Name of the current city being checked: " + curCity->getName());

        // check if the current stack top is the destination
        if (stack.peek().getName() == end) {
            status("A path from " + start + " to " + end + " has been found", 4);
            itineraries.push_back(stack);
            curCity->resetPaths();
            stack.pop();
            status(stack.toString(), 4);
        }
        // check if the current city has no more possible flights
        else if (curCity->isEnd()) {
            status("City " + curCity->getName() + " has no more possible flights", 4);
            curCity->resetPaths();
            stack.pop();
            status(stack.toString(), 4);
        }
        // iterate through the possible flights of the curCity
        else {
            // push the current possible flight to the stack if it doesn't already exist
            if (!isVisited(curCity->getCur())) {
                status("City " + curCity->getName() + " has a valid flight to " + curCity->getCur().getName(), 4);
                stack.push(curCity->getCur());
                status(stack.toString(), 4);
            }
            else
                status("Destination city " + curCity->getCur().getName() + " already exists in the stack");
            curCity->movePaths();
        }
    }
    return itineraries;
}

bool FlightPlanner::isVisited(DestinationCity city) {
    // temporary stack in order to iterate through the stack
    DSStack<DestinationCity> tempStack;

    // loop through the stack
    while (!stack.isEmpty()) {
        // check if the given city exists in the stack
        if (city.getName() == stack.peek().getName()) {
            // push the popped values back onto the stack
            while (!tempStack.isEmpty()) {
                stack.push(tempStack.peek());
                tempStack.pop();
            }
            return true;
        }
        tempStack.push(stack.peek());
        stack.pop();
    }

    // push the popped values back onto the stack
    while (!tempStack.isEmpty()) {
        stack.push(tempStack.peek());
        tempStack.pop();
    }
    return false;
}

int* FlightPlanner::calcPath(DSStack<DestinationCity>& s) {
    // temporary stack in order to iterate through the stack
    DSStack<DestinationCity> tempStack;

    // variables
    int time = 0, cost = 0;

    int count = 0;

    // move everything from the stack to the temp stack
    while (!s.isEmpty()) {
        tempStack.push(s.peek());
        s.pop();
        count++;
    }

    // loop through the temp stack, pushing back to the original stack as it goes
    time += (count-2)*43;
    cost += (count-2)*23;
    while (!tempStack.isEmpty()) {
        s.push(tempStack.peek());
        string prevAirline = tempStack.peek().getAirline();
        tempStack.pop();
        if (tempStack.isEmpty())
            continue;

        if (prevAirline != "" && prevAirline != tempStack.peek().getAirline())
            time += 27;

        // increment time and cost by the time and cost of the destination flight
        time += tempStack.peek().getTime();
        cost += tempStack.peek().getCost();
    }
    return new int[2]{time, cost};
}

int* FlightPlanner::writePath(DSStack<DestinationCity>& s, ofstream& out) {
    // temporary stack in order to iterate through the stack
    DSStack<DestinationCity> tempStack;

    // variables
    int time = 0, cost = 0;

    int count = 0;

    // move everything from the stack to the temp stack
    while (!s.isEmpty()) {
        tempStack.push(s.peek());
        s.pop();
        count++;
    }

    // name of the origin of a flight
    string origin = tempStack.peek().getName();

    // loop through the temp stack, pushing back to the original stack as it goes
    int layovers = ((count-2) < 0) ? 0 : (count-2);
    time += (count-2)*43;
    cost += (count-2)*23;
    while (!tempStack.isEmpty()) {
        s.push(tempStack.peek());
        string prevAirline = tempStack.peek().getAirline();
        tempStack.pop();
        if (tempStack.isEmpty())
            continue;

        if (prevAirline != "" && prevAirline != tempStack.peek().getAirline())
            time += 27;

        // print the name of the origin flight that was just popped,
        // and the information about the destination with time and cost
        out << "    " << origin << " -> ";
        out << tempStack.peek().getName() << " (";
        out << tempStack.peek().getAirline() << ")" << endl;
        //cout << "    " << origin << " -> ";
        //cout << tempStack.peek().getName() << " (";
        //cout << tempStack.peek().getAirline() << ")" << endl;
        origin = tempStack.peek().getName();

        // increment time and cost by the time and cost of the destination flight
        time += tempStack.peek().getTime();
        cost += tempStack.peek().getCost();
    }
    return new int[2]{time, cost};
}

void FlightPlanner::status(string status, int indent) {
    if (errorLevels[0]) {
        for (int i = 0; i < indent; i++)
            cout << " ";
        cout << "Status: " << status << endl;
    }
}

void FlightPlanner::warning(string warning, int indent) {
    if (errorLevels[1]) {
        for (int i = 0; i < indent; i++)
            cout << " ";
        cout << "Warning: " << warning << endl;
    }
}

void FlightPlanner::error(string error, int indent) {
    if (errorLevels[2]) {
        for (int i = 0; i < indent; i++)
            cout << " ";
        cout << "Error: " << error << endl;
    }
}