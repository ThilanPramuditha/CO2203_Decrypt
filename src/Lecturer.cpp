#include "Lecturer.h"
#include "Course.h" 
#include <iostream>
#include <limits> // Added for input validation

Lecturer::Lecturer(std::string id, std::string name) : Person(std::move(id), std::move(name)) {}

void Lecturer::openSession(Course* c) {
    std::cout << "Opening session for course...\n";
}

void Lecturer::closeSession(std::string sessionID) {
    std::cout << "Closing session: " << sessionID << "\n";
}

void Lecturer::displayMenu() {
    int choice = 0;
    while (choice != 4) { // Interactive menu loop
        std::cout << "\n--- Lecturer Dashboard ---\n";
        std::cout << "1. View Taught Courses\n";
        std::cout << "2. Open Attendance Session\n";
        std::cout << "3. Close Attendance Session\n";
        std::cout << "4. Logout\n";
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
                std::cout << "\n--- Taught Courses ---\n";
                if (taughtCourses.empty()) std::cout << "No courses assigned.\n";
                for (Course* c : taughtCourses) {
                    std::cout << *c << "\n"; // Relies on your overloaded operator<< in Course
                }
                break;
            case 2:
                std::cout << "\n--- Open Attendance Session ---\n";
                std::cout << "(Pending system integration)\n";
                break;
            case 3:
                std::cout << "\n--- Close Attendance Session ---\n";
                std::cout << "(Pending system integration)\n";
                break;
            case 4:
                std::cout << "Logging out...\n";
                break;
            default:
                std::cout << "[ERROR] Invalid choice.\n";
        }
    }
}