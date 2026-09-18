#include "Course.h"
#include "Student.h"
#include <utility>

Course::Course(std::string code, std::string t, int cap, TimetableSlot sched)
    : courseCode(std::move(code)), title(std::move(t)), capacity(cap), schedule(sched) {}

Course::~Course() {}

TimetableSlot Course::getSchedule() const {
    return schedule;
}

bool Course::isStudentEnrolled(const std::string& studentID) const {
    for (const Student* s : enrolledStudents) {
        if (s->getID() == studentID) {
            return true;
        }
    }
    return false;
}

#include <algorithm>
void Course::removeStudent(Student* s) {
    auto it = std::find(enrolledStudents.begin(), enrolledStudents.end(), s);
    if (it != enrolledStudents.end()) {
        enrolledStudents.erase(it);
    }
}

std::ostream& operator<<(std::ostream& os, const Course& c) {
    os << c.getCourseType() << "," << c.courseCode << "," << c.title << "," << c.capacity;
    return os;
}