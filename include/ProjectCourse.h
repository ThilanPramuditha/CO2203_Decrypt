#ifndef PROJECT_COURSE_H
#define PROJECT_COURSE_H

#include "Course.h"
#include <string>

class ProjectCourse : public Course {
private:
    std::string supervisorID;

public:
    bool isEligible(Student* s) const override;
};

#endif // PROJECT_COURSE_H