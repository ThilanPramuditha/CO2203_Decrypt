#include "Person.h"
#include <utility>

Person::Person(std::string id, std::string name) 
    : userID(std::move(id)), name(std::move(name)), email("") {}

Person::~Person() {}

std::string Person::getID() const {
    return userID;
}

std::string Person::getName() const {
    return name;
}

