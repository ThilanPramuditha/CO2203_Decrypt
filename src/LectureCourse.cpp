#include "LectureCourse.h"
#include "CustomExceptions.h"
#include "Student.h"


LectureCourse::LectureCourse(std::string code, std::string t, int credits, int cap,
                             TimetableSlot ts)
    : Course(std::move(code), std::move(t), credits, cap, ts) {}

void LectureCourse::checkEligibility(Student *s) const {
    if (getEnrolledCount() >= static_cast<size_t>(getCapacity())) {
        throw CapacityException("Course is at full capacity.");
    }

    if (!checkPrerequisitesRecursively(s)) {
        throw CustomException("Prerequisites not met for this course (chain violation).");
    }
}

std::string LectureCourse::getGradingBehaviour() const {
    return "70% Final Exam 30% Continuous Assessment";
}