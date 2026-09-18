#include "Lecturer.h"
#include "Course.h" 
#include <iostream>
#include <limits> // Added for input validation

#include "QRCodeCapture.h"
#include "ConsoleCardReader.h"
#include "AttendanceRegister.h"
#include "AttendanceSession.h"
#include "CustomExceptions.h"
#include "RegistrationSystem.h"

Lecturer::Lecturer(std::string id, std::string name) : Person(std::move(id), std::move(name)) {}

void Lecturer::openSession(Course* c) {
    std::cout << "Opening session for course " << c->getCourseCode() << "...\n";
    AttendanceRegister* reg = c->getRegister();
    reg->openSession(c->getSchedule());
    
    AttendanceSession* session = reg->getActiveSession();
    if (!session) {
        std::cout << "[ERROR] Failed to open session.\n";
        return;
    }
    
    QRCodeCapture reader;
    session->setCaptureMechanism(&reader);
    
    try {
        session->executeCapture(reg);
    } catch (const CustomException& e) {
        std::cout << "[ERROR] " << e.what() << "\n";
    }
}

void Lecturer::closeSession(std::string sessionID) {
    std::cout << "Closing session: " << sessionID << "\n";
}

void Lecturer::displayMenu(RegistrationSystem* sys) {
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
            case 2: {
                std::cout << "\n--- Open Attendance Session ---\n";
                const auto& courses = sys->getCourses();
                if (courses.empty()) {
                    std::cout << "No courses available.\n";
                    break;
                }
                std::cout << "Available Courses:\n";
                for (Course* c : courses) {
                    std::cout << *c << "\n";
                }
                
                std::cout << "\nEnter Course Code to open session: ";
                std::string code;
                std::cin >> code;
                
                // Clear the newline left in the input buffer by std::cin >>
                // This prevents the next std::getline in ConsoleCardReader from reading an empty string and exiting immediately.
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                Course* target = sys->findCourse(code);
                if (!target) {
                    std::cout << "[ERROR] Course not found.\n";
                    break;
                }
                
                openSession(target);
                break;
            }
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