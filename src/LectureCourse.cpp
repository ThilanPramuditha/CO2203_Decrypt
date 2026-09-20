#include "LectureCourse.h"
#include "CustomExceptions.h"
#include "Student.h"


LectureCourse::LectureCourse(std::string code, std::string t, int credits, int cap,
                             TimetableSlot ts)
    : Course(std::move(code), std::move(t), credits, cap, ts) {}

void LectureCourse::checkEligibility(Student *s) const {
    bool preqError = !checkPrerequisitesRecursively(s);
    bool capError = getEnrolledCount() >= static_cast<size_t>(getCapacity());
    
    if (preqError && capError) {
        throw CapacityException("Prerequisites not met for this course.\n[BLOCKED BY SYSTEM] Course is at full capacity.");
    } else if (preqError) {
        throw CustomException("Prerequisites not met for this course.");
    } else if (capError) {
        throw CapacityException("Course is at full capacity.");
    }
}

std::string LectureCourse::getGradingBehaviour() const {
    return "70% Final Exam 30% Continuous Assessment";
}