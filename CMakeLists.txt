cmake_minimum_required(VERSION 3.15)
project(21f_flight_planner)

set(CMAKE_CXX_STANDARD 14)

configure_file(data/sample01-flight-data.txt data/sample01-flight-data.txt COPYONLY)
configure_file(data/sample01-req-flights.txt data/sample01-req-flights.txt COPYONLY)
configure_file(data/sample02-flight-data.txt data/sample02-flight-data.txt COPYONLY)
configure_file(data/sample02-req-flights.txt data/sample02-req-flights.txt COPYONLY)
configure_file(data/sample03-flight-data.txt data/sample03-flight-data.txt COPYONLY)
configure_file(data/sample03-req-flights.txt data/sample03-req-flights.txt COPYONLY)
configure_file(data/f.txt data/f.txt COPYONLY)
configure_file(data/r.txt data/r.txt COPYONLY)

add_executable(21f_flight_planner main.cpp DSLinkedList.h DSStack.h OriginCity.cpp DestinationCity.cpp FlightPlanner.cpp)
add_executable(21f_flight_planner_test catch_setup.cpp sample_tests.cpp DSLinkedList.h DSStack.h)
