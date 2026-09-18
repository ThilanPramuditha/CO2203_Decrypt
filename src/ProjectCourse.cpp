#include "ProjectCourse.h"
#include "Student.h"
#include "CustomExceptions.h"
#include <utility>

ProjectCourse::ProjectCourse(std::string code, std::string t, int cap,
                             TimetableSlot ts)
    : Course(std::move(code), std::move(t), cap, ts) {}

void ProjectCourse::checkEligibility(Student *s) const {
    if (getEnrolledCount() >= static_cast<size_t>(getCapacity())) {
        throw CapacityException("Course is at full capacity.");
    }

    for (Course* prereq : getPrerequisites()) {
        if (!s->hasCompleted(prereq)) {
            throw CustomException("Prerequisites not met for this course.");
        }
    }
}