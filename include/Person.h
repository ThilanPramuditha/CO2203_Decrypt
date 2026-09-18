#ifndef PERSON_H
#define PERSON_H

#include <string>

class RegistrationSystem;

class Person {
private:
    std::string userID;
    std::string name;
    std::string email;

public:
    Person(std::string id, std::string name);
    virtual ~Person(); 

    std::string getID() const;
    
    virtual void displayMenu(RegistrationSystem* sys) = 0; 
};

#endif // PERSON_H