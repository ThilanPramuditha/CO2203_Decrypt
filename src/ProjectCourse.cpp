#include "ProjectCourse.h"
#include "Student.h"
#include "CustomExceptions.h"
#include <utility>

ProjectCourse::ProjectCourse(std::string code, std::string t, int credits, int cap,
                             TimetableSlot ts)
    : Course(std::move(code), std::move(t), credits, cap, ts) {}

void ProjectCourse::checkEligibility(Student *s) const {
    if (getEnrolledCount() >= static_cast<size_t>(getCapacity())) {
        throw CapacityException("Course is at full capacity.");
    }

    if (!checkPrerequisitesRecursively(s)) {
        throw CustomException("Prerequisites not met for this course (chain violation).");
    }
}

std::string ProjectCourse::getGradingBehaviour() const {
    return "100% Final Project Submission";
}