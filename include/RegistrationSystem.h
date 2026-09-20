#ifndef REGISTRATION_SYSTEM_H
#define REGISTRATION_SYSTEM_H

#include <vector>
#include "Person.h"
#include "Course.h"
#include "Repository.h"

class RegistrationSystem {
private:
    std::vector<Person*> usersList;
    std::vector<Course*> coursesList;
    
    Repository<Person> userRepo;
    Repository<Course> courseRepo;

public:
    RegistrationSystem();
    ~RegistrationSystem(); 

    // Rule of Three/Five: Explicitly delete copy constructor and assignment operator
    RegistrationSystem(const RegistrationSystem&) = delete;
    RegistrationSystem& operator=(const RegistrationSystem&) = delete;

    void run();
    Person* loginUser();
    void loadSystemData();
    void saveSystemData();

    const std::vector<Course*>& getCourses() const;
    const std::vector<Person*>& getUsers() const;
    
    void addUser(Person* p);
    void removeUser(const std::string& userID);
    void addCourse(Course* c);
    void removeCourse(const std::string& courseCode);

    Course* findCourse(const std::string& courseCode) const;
};

#endif
