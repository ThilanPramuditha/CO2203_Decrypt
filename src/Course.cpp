#include "Course.h"
#include "Student.h"
#include <utility>

Course::Course(std::string code, std::string t, int c, int cap, TimetableSlot sched)
    : courseCode(std::move(code)), title(std::move(t)), credits(c), capacity(cap), schedule(sched) {}

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

bool Course::checkPrerequisitesRecursively(Student* s) const {
    std::vector<Course*> queue = prerequisites;
    for (size_t i = 0; i < queue.size(); ++i) {
        Course* prereq = queue[i];
        if (!s->hasCompleted(prereq)) {
            return false;
        }
        for (Course* p : prereq->getPrerequisites()) {
            if (std::find(queue.begin(), queue.end(), p) == queue.end()) {
                queue.push_back(p);
            }
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const Course& c) {
    os << c.getCourseType() << "," << c.courseCode << "," << c.title << "," << c.credits << "," << c.getGradingBehaviour() << "," << c.capacity;
    return os;
}