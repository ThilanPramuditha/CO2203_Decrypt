#include "Course.h"
#include <iostream>

Course::Course(std::string code, std::string t, int cap, TimetableSlot ts) 
    : courseCode(std::move(code)), title(std::move(t)), capacity(cap), schedule(ts), registerSheet() {}

TimetableSlot Course::getSchedule() const {
    return schedule;
}

std::ostream& operator<<(std::ostream& os, const Course& c) {
    os << "Course Code: " << c.courseCode << " | Title: " << c.title;
    return os;
}