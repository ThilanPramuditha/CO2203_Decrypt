#include "Course.h"
#include <utility>

Course::Course(std::string code, std::string t, int cap, TimetableSlot sched)
    : courseCode(std::move(code)), title(std::move(t)), capacity(cap), schedule(sched) {}

Course::~Course() {}

TimetableSlot Course::getSchedule() const {
    return schedule;
}

// FIX: Enforced strict CSV formatting
std::ostream& operator<<(std::ostream& os, const Course& c) {
    os << "LectureCourse," << c.courseCode << "," << c.title << "," << c.capacity;
    return os;
}