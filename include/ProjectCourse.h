#ifndef PROJECT_COURSE_H
#define PROJECT_COURSE_H

#include "Course.h"
#include <string>

class ProjectCourse : public Course {
private:
  std::string supervisorID;

public:
  ProjectCourse(std::string code, std::string title, int cap,
                TimetableSlot sched, std::string supervisor);
  bool isEligible(Student *s) const override;
  std::string getCourseType() const override { return "ProjectCourse"; }
};

#endif // PROJECT_COURSE_H