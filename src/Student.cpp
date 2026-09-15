#include "Student.h"
#include "Course.h"
#include "CustomExceptions.h"
#include <iostream>
#include <algorithm>

Student::Student(std::string id, std::string name) : Person(std::move(id), std::move(name)) {}

void Student::enrol(Course* c) {
    if (!c->isEligible(this)) {
        throw CustomException("Student failed eligibility checks for this course.");
    }
    
    if (personalTimetable.checkClash(c->getSchedule())) {
        throw ClashException("Timetable clash detected with an existing course.");
    }
    
    enrolledCourses.push_back(c);
    personalTimetable.addSlot(c->getSchedule());
}

void Student::dropCourse(Course* c) {
    auto it = std::find(enrolledCourses.begin(), enrolledCourses.end(), c);
    if (it != enrolledCourses.end()) {
        enrolledCourses.erase(it);
    }
}

bool Student::hasCompleted(Course* c) const {
    return std::find(completedCourses.begin(), completedCourses.end(), c) != completedCourses.end();
}

void Student::displayMenu() {
    std::cout << "--- Student Dashboard ---\n";
    std::cout << "1. View Timetable\n";
    std::cout << "2. Enrol in Course\n";
    std::cout << "3. Drop Course\n";
}

std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << "Student [ID: " << s.getID() << "]";
    return os;
}