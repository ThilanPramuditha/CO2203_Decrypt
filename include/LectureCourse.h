#ifndef LECTURE_COURSE_H
#define LECTURE_COURSE_H

#include "Course.h"
#include <string>

class LectureCourse : public Course {
public:
  LectureCourse(std::string code, std::string title, int credits, int cap,
                TimetableSlot sched);

  void checkEligibility(Student *s) const override;
  std::string getCourseType() const override { return "LectureCourse"; }
  std::string getGradingBehaviour() const override;
};

#endif
