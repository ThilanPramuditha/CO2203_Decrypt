#include "ProjectCourse.h"
#include "CustomExceptions.h"
#include "Student.h"


ProjectCourse::ProjectCourse(std::string code, std::string t, int cap,
                             TimetableSlot ts, std::string supervisor)
    : Course(std::move(code), std::move(t), cap, ts),
      supervisorID(std::move(supervisor)) {}

bool ProjectCourse::isEligible(Student *s) const {
  if (getEnrolledCount() >= static_cast<size_t>(getCapacity())) {
    return false;
  }

  for (Course *prereq : getPrerequisites()) {
    if (!s->hasCompleted(prereq)) {
      return false;
    }
  }
  return true;
}