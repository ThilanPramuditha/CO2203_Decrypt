#ifndef LECTURE_COURSE_H
#define LECTURE_COURSE_H

#include "Course.h"
#include <string>

class LectureCourse : public Course {
public:
  LectureCourse(std::string code, std::string title, int cap,
                TimetableSlot sched);

  bool isEligible(Student *s) const override;
};

#endif // LECTURE_COURSE_H