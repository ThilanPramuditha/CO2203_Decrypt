#ifndef LAB_COURSE_H
#define LAB_COURSE_H

#include "Course.h"

class LabCourse : public Course {
private:
    int labGroupSize;

public:
    bool isEligible(Student* s) const override;
};

#endif // LAB_COURSE_H