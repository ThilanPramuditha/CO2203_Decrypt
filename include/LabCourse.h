#ifndef LAB_COURSE_H
#define LAB_COURSE_H

#include "Course.h"
#include <string>

class LabCourse : public Course {
private:
  int labGroupSize;

public:
  LabCourse(std::string code, std::string title, int cap, TimetableSlot sched,
            int groupSize);

  bool isEligible(Student *s) const override;
};

#endif // LAB_COURSE_H