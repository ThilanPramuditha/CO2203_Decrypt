#include "LabCourse.h"
#include "CustomExceptions.h"
#include "Student.h"

LabCourse::LabCourse(std::string code, std::string t, int credits, int cap, TimetableSlot ts,
                     int groupSize)
    : Course(std::move(code), std::move(t), credits, cap, ts), labGroupSize(groupSize) {}

void LabCourse::checkEligibility(Student *s) const {
    if (getEnrolledCount() >= static_cast<size_t>(labGroupSize)) {
        throw CapacityException("Course is at full capacity.");
    }

    if (!checkPrerequisitesRecursively(s)) {
        throw CustomException("Prerequisites not met for this course (chain violation).");
    }
}

std::string LabCourse::getGradingBehaviour() const {
    return "50% Practical 50% Final Exam";
}