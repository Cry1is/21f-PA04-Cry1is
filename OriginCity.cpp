//
// Created by Zachary on 11/1/2021.
//

#include "OriginCity.h"

OriginCity::OriginCity() {
    this->name = "";
}

OriginCity::OriginCity(string name) {
    this->name = name;
}

void OriginCity::setName(string name) {
    this->name = name;
}

string OriginCity::getName() {
    return this->name;
}

void OriginCity::setPaths(DSLinkedList<DestinationCity>& paths) {
    this->paths = paths;
}

DSLinkedList<DestinationCity>& OriginCity::getPaths() {
    return this->paths;
}

void OriginCity::addPath(DestinationCity& path) {
    if (!this->paths.contains(path))
        this->paths.push_back(path);
}

void OriginCity::movePaths() {
    this->paths.moveItr();
}

void OriginCity::resetPaths() {
    this->paths.resetItr();
}

DestinationCity& OriginCity::getCur() {
    return this->paths.getItr()->data;
}

bool OriginCity::isEnd() {
    return this->paths.getItr() == nullptr;
}

bool OriginCity::operator==(OriginCity& other) {
    return this->name == other.getName();
}

std::ostream& operator<<(std::ostream& fout, const OriginCity& o) {
    fout << o.name;
    return fout;
}