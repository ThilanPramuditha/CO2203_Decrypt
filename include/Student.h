#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include "Timetable.h" 
#include <vector>
#include <ostream>

class Course; 

class Student : public Person {
private:
    std::vector<Course*> enrolledCourses;
    std::vector<Course*> completedCourses;
    Timetable personalTimetable;

public:
    Student(std::string id, std::string name);

    void enrol(Course* c);
    void dropCourse(Course* c);
    void displayMenu() override;

    friend std::ostream& operator<<(std::ostream& os, const Student& s);
};

#endif // STUDENT_H