#include "LabCourse.h"
#include "CustomExceptions.h"
#include "Student.h"

LabCourse::LabCourse(std::string code, std::string t, int cap, TimetableSlot ts,
                     int groupSize)
    : Course(std::move(code), std::move(t), cap, ts), labGroupSize(groupSize) {}

void LabCourse::checkEligibility(Student *s) const {
    if (getEnrolledCount() >= static_cast<size_t>(labGroupSize)) {
        throw CapacityException("Course is at full capacity.");
    }

    for (Course* prereq : getPrerequisites()) {
        if (!s->hasCompleted(prereq)) {
            throw CustomException("Prerequisites not met for this course.");
        }
    }
}