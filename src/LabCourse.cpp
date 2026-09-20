#include "LabCourse.h"
#include "CustomExceptions.h"
#include "Student.h"

LabCourse::LabCourse(std::string code, std::string t, int credits, int cap, TimetableSlot ts,
                     int groupSize)
    : Course(std::move(code), std::move(t), credits, cap, ts), labGroupSize(groupSize) {}

void LabCourse::checkEligibility(Student *s) const {
    bool preqError = !checkPrerequisitesRecursively(s);
    bool capError = getEnrolledCount() >= static_cast<size_t>(labGroupSize);
    
    if (preqError && capError) {
        throw CapacityException("Prerequisites not met for this course (chain violation).\n[BLOCKED BY SYSTEM] Course is at full capacity.");
    } else if (preqError) {
        throw CustomException("Prerequisites not met for this course (chain violation).");
    } else if (capError) {
        throw CapacityException("Course is at full capacity.");
    }
}

std::string LabCourse::getGradingBehaviour() const {
    return "50% Practical 50% Final Exam";
}