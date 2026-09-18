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
    void displayMenu(RegistrationSystem* sys) override;
    
    const std::vector<Course*>& getEnrolledCourses() const { return enrolledCourses; }
    
    std::string getRole() const override { return "Student"; }
    
    bool hasCompleted(Course* c) const;

    friend std::ostream& operator<<(std::ostream& os, const Student& s);
};

#endif
