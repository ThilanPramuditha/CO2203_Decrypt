#include "LabCourse.h"
#include "CustomExceptions.h"
#include "Student.h"

LabCourse::LabCourse(std::string code, std::string t, int cap, TimetableSlot ts,
                     int groupSize)
    : Course(std::move(code), std::move(t), cap, ts), labGroupSize(groupSize) {}

bool LabCourse::isEligible(Student *s) const {
    if (getEnrolledCount() >= static_cast<size_t>(labGroupSize)) {
        return false;
    }

    for (Course* prereq : getPrerequisites()) {
        if (!s->hasCompleted(prereq)) {
            return false;
        }
    }
    
    return true;
}