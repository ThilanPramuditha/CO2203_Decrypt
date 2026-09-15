#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
#include <ostream>
#include "TimetableSlot.h" 
#include "AttendanceRegister.h" 

class Student; 

class Course {
private:
    std::string courseCode;
    std::string title;
    int capacity;
    std::vector<Student*> enrolledStudents;
    std::vector<Course*> prerequisites;
    
    TimetableSlot schedule;
    AttendanceRegister registerSheet; 

public:
    virtual ~Course() = default;

    TimetableSlot getSchedule() const;
    virtual bool isEligible(Student* s) const = 0; 

    friend std::ostream& operator<<(std::ostream& os, const Course& c);
};

#endif // COURSE_H