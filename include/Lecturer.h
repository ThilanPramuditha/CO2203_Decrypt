#ifndef LECTURER_H
#define LECTURER_H

#include "Person.h"
#include <vector>
#include <string>

class Course; 

class Lecturer : public Person {
private:
    std::vector<Course*> taughtCourses;

public:
    Lecturer(std::string id, std::string name);

    void addTaughtCourse(Course* c) { taughtCourses.push_back(c); }
    const std::vector<Course*>& getTaughtCourses() const { return taughtCourses; }

    void openSession(Course* c);
    void closeSession(std::string sessionID);
    void viewEnrolmentList();
    void viewAttendancePercentages();
    void displayMenu(RegistrationSystem* sys) override;
    
    std::string getRole() const override { return "Lecturer"; }
};

#endif
