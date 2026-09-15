#include "ProjectCourse.h"
#include "Student.h"
#include "CustomExceptions.h"

ProjectCourse::ProjectCourse(std::string code, std::string t, int cap, TimetableSlot ts, std::string supervisor)
    : Course(std::move(code), std::move(t), cap, ts), supervisorID(std::move(supervisor)) {}

bool ProjectCourse::isEligible(Student* s) const {
    if (getEnrolledCount() >= getCapacity()) {
        throw CapacityException("Project course is full.");
    }
    
    for (Course* prereq : getPrerequisites()) {
        if (!s->hasCompleted(prereq)) {
            return false;
        }
    }
    return true;
}