#ifndef LECTURE_COURSE_H
#define LECTURE_COURSE_H

#include "Course.h"

class LectureCourse : public Course {
public:
    bool isEligible(Student* s) const override;
};

#endif // LECTURE_COURSE_H