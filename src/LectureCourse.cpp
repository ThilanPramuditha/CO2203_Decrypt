#include "LectureCourse.h"
#include "CustomExceptions.h"
#include "Student.h"


LectureCourse::LectureCourse(std::string code, std::string t, int cap,
                             TimetableSlot ts)
    : Course(std::move(code), std::move(t), cap, ts) {}

void LectureCourse::checkEligibility(Student *s) const {
    if (getEnrolledCount() >= static_cast<size_t>(getCapacity())) {
        throw CapacityException("Course is at full capacity.");
    }

    for (Course* prereq : getPrerequisites()) {
        if (!s->hasCompleted(prereq)) {
            throw CustomException("Prerequisites not met for this course.");
        }
    }
}