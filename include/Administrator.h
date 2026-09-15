#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "Person.h"
#include <string>

class Administrator : public Person {
public:
    Administrator(std::string id, std::string name);

    void createUser();
    void updateUser(std::string userID);
    void removeUser(std::string userID);
    void createCourse();
    void editCourse(std::string courseCode);
    void removeCourse(std::string courseCode);
    void generateReport();
    void displayMenu() override;
};

#endif // ADMINISTRATOR_H