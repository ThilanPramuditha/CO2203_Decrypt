#include "ProjectCourse.h"
#include "Student.h"
#include "CustomExceptions.h"
#include <utility>

ProjectCourse::ProjectCourse(std::string code, std::string t, int credits, int cap,
                             TimetableSlot ts)
    : Course(std::move(code), std::move(t), credits, cap, ts) {}

void ProjectCourse::checkEligibility(Student *s) const {
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

std::string ProjectCourse::getGradingBehaviour() const {
    return "100% Final Project Submission";
}