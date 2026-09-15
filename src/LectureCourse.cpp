#include "LectureCourse.h"
#include "CustomExceptions.h"

LectureCourse::LectureCourse(std::string code, std::string t, int cap, TimetableSlot ts)
    : Course(std::move(code), std::move(t), cap, ts) {}

bool LectureCourse::isEligible(Student* s) const {
    if (getEnrolledCount() >= getCapacity()) {
        throw CapacityException("Lecture course has reached maximum seat capacity.");
    }
    return true; 
}