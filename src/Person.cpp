#include "Person.h"

Person::Person(std::string id, std::string name) : userID(std::move(id)), name(std::move(name)) {}

std::string Person::getID() const {
    return userID;
}