#include "LectureCourse.h"
#include "CustomExceptions.h"
#include "Student.h"


LectureCourse::LectureCourse(std::string code, std::string t, int cap,
                             TimetableSlot ts)
    : Course(std::move(code), std::move(t), cap, ts) {}

bool LectureCourse::isEligible(Student *s) const {
    if (getEnrolledCount() >= static_cast<size_t>(getCapacity())) {
        return false;
    }

    for (Course* prereq : getPrerequisites()) {
        if (!s->hasCompleted(prereq)) {
            return false;
        }
    }
    
    return true;
}