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
    std::string supervisorID;
    std::vector<Student*> enrolledStudents;
    std::vector<Course*> prerequisites;
    
    TimetableSlot schedule;
    AttendanceRegister registerSheet; 

public:
    Course(std::string code, std::string title, int capacity, TimetableSlot schedule);
    virtual ~Course();

    TimetableSlot getSchedule() const;
    std::string getCourseCode() const { return courseCode; }
    
    void setTitle(const std::string& newTitle) { title = newTitle; }
    void setCapacity(int cap) { capacity = cap; }
    
    void setSupervisorID(const std::string& id) { supervisorID = id; }
    std::string getSupervisorID() const { return supervisorID; }
    
    AttendanceRegister* getRegister() { return &registerSheet; }
    virtual std::string getCourseType() const = 0;
    virtual void checkEligibility(Student* s) const = 0; 
    bool isStudentEnrolled(const std::string& studentID) const;
    
    int getCapacity() const { return capacity; }
    size_t getEnrolledCount() const { return enrolledStudents.size(); }
    const std::vector<Course*>& getPrerequisites() const { return prerequisites; }
    void addPrerequisite(Course* c) { prerequisites.push_back(c); }

    void addStudent(Student* s) { enrolledStudents.push_back(s); }
    void removeStudent(Student* s);

    friend std::ostream& operator<<(std::ostream& os, const Course& c);
};

#endif
