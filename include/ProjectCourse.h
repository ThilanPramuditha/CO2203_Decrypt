#ifndef PROJECT_COURSE_H
#define PROJECT_COURSE_H

#include "Course.h"
#include <string>

class ProjectCourse : public Course {
public:
  ProjectCourse(std::string code, std::string title, int credits, int cap,
                TimetableSlot sched);
  void checkEligibility(Student *s) const override;
  std::string getCourseType() const override { return "ProjectCourse"; }
  std::string getGradingBehaviour() const override;
};

#endif
