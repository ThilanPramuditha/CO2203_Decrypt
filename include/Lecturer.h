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

    void openSession(Course* c);
    void closeSession(std::string sessionID);
    
    void displayMenu(RegistrationSystem* sys) override;
};

#endif // LECTURER_H