#include "Administrator.h"
#include "Student.h"
#include "Lecturer.h"
#include "LectureCourse.h"
#include "LabCourse.h"
#include "ProjectCourse.h"
#include "RegistrationSystem.h"
#include <iostream>
#include <limits> 
#include <algorithm> 

Administrator::Administrator(std::string id, std::string name) : Person(std::move(id), std::move(name)) {}

void Administrator::createUser() { 
    if (!sysRef) return;
    std::cout << "Enter Role (Student/Lecturer/Administrator): ";
    std::string role; std::cin >> role;
    std::cout << "Enter ID: ";
    std::string id; std::cin >> id;
    
    const auto& users = sysRef->getUsers();
    auto userIt = std::find_if(users.begin(), users.end(), [&](Person* p) { return p->getID() == id; });
    if (userIt != users.end()) {
        std::cout << "[ERROR] A user with this ID already exists.\n";
        return;
    }
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter Name: ";
    std::string name; std::getline(std::cin, name);
    
    Person* p = nullptr;
    if (role == "Student") p = new Student(id, name);
    else if (role == "Lecturer") p = new Lecturer(id, name);
    else if (role == "Administrator") p = new Administrator(id, name);
    else { std::cout << "[ERROR] Invalid role.\n"; return; }
    
    sysRef->addUser(p);
    std::cout << "[SUCCESS] User created.\n";
}

void Administrator::updateUser(std::string userID) { 
    if (!sysRef) return;
    const auto& users = sysRef->getUsers();
    auto it = std::find_if(users.begin(), users.end(), [&](Person* p) { return p->getID() == userID; });
    if (it != users.end()) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter new Name: ";
        std::string newName; std::getline(std::cin, newName);
        (*it)->setName(newName);
        std::cout << "[SUCCESS] User name updated.\n";
    } else {
        std::cout << "[ERROR] User not found.\n";
    }
}

void Administrator::removeUser(std::string userID) { 
    if (sysRef) sysRef->removeUser(userID); 
}

void Administrator::createCourse() { 
    if (!sysRef) return;
    std::cout << "Enter Course Type (Lecture/Lab/Project): ";
    std::string type; std::cin >> type;
    std::cout << "Enter Course Code: ";
    std::string code; std::cin >> code;
    
    if (sysRef->findCourse(code) != nullptr) {
        std::cout << "[ERROR] A course with this code already exists.\n";
        return;
    }
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter Title: ";
    std::string title; std::getline(std::cin, title);
    std::cout << "Enter Capacity: ";
    int cap; std::cin >> cap;
    
    std::cout << "Enter Supervisor ID (Lecturer): ";
    std::string supervisor; std::cin >> supervisor;

    std::cout << "Enter Timetable Day (1=Mon, 7=Sun): ";
    int day; std::cin >> day;
    std::cout << "Enter Start Time (e.g., 800): ";
    int start; std::cin >> start;
    std::cout << "Enter End Time (e.g., 1000): ";
    int end; std::cin >> end;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter Location: ";
    std::string loc; std::getline(std::cin, loc);
    
    TimetableSlot slot(day, start, end, loc);
    
    Course* c = nullptr;
    if (type == "Lecture") c = new LectureCourse(code, title, cap, slot);
    else if (type == "Lab") {
        std::cout << "Enter Lab Group Size: ";
        int size; std::cin >> size;
        c = new LabCourse(code, title, cap, slot, size);
    }
    else if (type == "Project") c = new ProjectCourse(code, title, cap, slot);
    else { std::cout << "[ERROR] Invalid course type.\n"; return; }
    
    c->setSupervisorID(supervisor);
    sysRef->addCourse(c);
    std::cout << "[SUCCESS] Course created.\n";
}

void Administrator::editCourse(std::string courseCode) { 
    if (!sysRef) return;
    Course* target = sysRef->findCourse(courseCode);
    if (target) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter new Title: ";
        std::string newTitle; std::getline(std::cin, newTitle);
        std::cout << "Enter new Capacity: ";
        int cap; std::cin >> cap;
        
        target->setTitle(newTitle);
        target->setCapacity(cap);
        std::cout << "[SUCCESS] Course updated.\n";
    } else {
        std::cout << "[ERROR] Course not found.\n";
    }
}

void Administrator::removeCourse(std::string courseCode) { 
    if (sysRef) sysRef->removeCourse(courseCode); 
}

void Administrator::generateReport() { 
    if (!sysRef) return;
    std::cout << "\n=== SYSTEM REPORT ===\n";
    std::cout << "Users in System: " << sysRef->getUsers().size() << "\n";
    for (Person* p : sysRef->getUsers()) {
        std::cout << "- " << p->getRole() << ": " << p->getID() << " (" << p->getName() << ")\n";
    }
    
    std::cout << "\nCourses in System: " << sysRef->getCourses().size() << "\n";
    for (Course* c : sysRef->getCourses()) {
        std::cout << "- " << *c << " (Enrolled: " << c->getEnrolledCount() << "/" << c->getCapacity() << ")\n";
    }
    std::cout << "=====================\n";
}

void Administrator::displayMenu(RegistrationSystem* sys) {
    std::cout << "\n--- Welcome back, Administrator " << this->getName() << "! ---\n";
    int choice = 0;
    while (choice != 8) {
        std::cout << "\n--- Administrator Dashboard ---\n";
        std::cout << "1. Create User\n";
        std::cout << "2. Update User\n";
        std::cout << "3. Remove User\n";
        std::cout << "4. Create Course\n";
        std::cout << "5. Edit Course\n";
        std::cout << "6. Remove Course\n";
        std::cout << "7. Generate System Report\n";
        std::cout << "8. Logout\n";
        std::cout << "Enter choice: ";
        
        if (!(std::cin >> choice)) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "[ERROR] Invalid input.\n";
            continue;
        }

        switch (choice) {
            case 1:
                createUser();
                break;
            case 2: {
                std::string id;
                std::cout << "Enter User ID to update: ";
                std::cin >> id;
                updateUser(id);
                break;
            }
            case 3: {
                std::string id;
                std::cout << "Enter User ID to remove: ";
                std::cin >> id;
                removeUser(id);
                break;
            }
            case 4:
                createCourse();
                break;
            case 5: {
                std::string code;
                std::cout << "Enter Course Code to edit: ";
                std::cin >> code;
                editCourse(code);
                break;
            }
            case 6: {
                std::string code;
                std::cout << "Enter Course Code to remove: ";
                std::cin >> code;
                removeCourse(code);
                break;
            }
            case 7:
                generateReport();
                break;
            case 8:
                std::cout << "Logging out...\n";
                break;
            default:
                std::cout << "[ERROR] Invalid choice.\n";
        }
    }
}