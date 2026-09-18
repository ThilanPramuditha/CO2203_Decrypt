#include "Administrator.h"
#include <iostream>
#include <limits> // Added for input validation

Administrator::Administrator(std::string id, std::string name) : Person(std::move(id), std::move(name)) {}

void Administrator::createUser() { std::cout << "Creating new user...\n"; }
void Administrator::updateUser(std::string userID) { std::cout << "Updating user...\n"; }
void Administrator::removeUser(std::string userID) { std::cout << "Removing user...\n"; }
void Administrator::createCourse() { std::cout << "Creating new course...\n"; }
void Administrator::editCourse(std::string courseCode) { std::cout << "Editing course...\n"; }
void Administrator::removeCourse(std::string courseCode) { std::cout << "Removing course...\n"; }
void Administrator::generateReport() { std::cout << "Generating system report...\n"; }

void Administrator::displayMenu(RegistrationSystem* sys) {
    int choice = 0;
    while (choice != 5) { // Interactive menu loop
        std::cout << "\n--- Administrator Dashboard ---\n";
        std::cout << "1. Create User\n";
        std::cout << "2. Remove User\n";
        std::cout << "3. Create Course\n";
        std::cout << "4. Generate System Report\n";
        std::cout << "5. Logout\n";
        std::cout << "Enter choice: ";
        
        // Input error handling
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
                std::cout << "Enter User ID to remove: ";
                std::cin >> id;
                removeUser(id);
                break;
            }
            case 3:
                createCourse();
                break;
            case 4:
                generateReport();
                break;
            case 5:
                std::cout << "Logging out...\n";
                break;
            default:
                std::cout << "[ERROR] Invalid choice.\n";
        }
    }
}