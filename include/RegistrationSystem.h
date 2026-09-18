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
    
    // Aggregation of the generic repositories
    Repository<Person> userRepo;
    Repository<Course> courseRepo;

public:
    RegistrationSystem();
    ~RegistrationSystem(); 

    void run();
    Person* loginUser();
    void loadSystemData();
    void saveSystemData();

    const std::vector<Course*>& getCourses() const;
    Course* findCourse(const std::string& courseCode) const;
};

#endif // REGISTRATION_SYSTEM_H