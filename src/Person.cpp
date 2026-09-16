#include "Person.h"
#include <utility> // for std::move

Person::Person(std::string id, std::string name) 
    : userID(std::move(id)), name(std::move(name)), email("") {}

Person::~Person() {}

std::string Person::getID() const {
    return userID;
}
