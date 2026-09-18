#include "RegistrationSystem.h"
#include <iostream>
#include "Student.h"
#include "Lecturer.h"
#include "Administrator.h"
#include "LectureCourse.h"
#include "LabCourse.h"
#include "ProjectCourse.h"
#include "TimetableSlot.h"
#include "CustomExceptions.h"
#include "FileReplayCapture.h"

// Initialize the file paths via the constructor initialization list
RegistrationSystem::RegistrationSystem() 
    : userRepo("data/users_data.csv"), courseRepo("data/courses_data.csv") {}

// Destructor to safely clean up dynamically allocated memory
RegistrationSystem::~RegistrationSystem() {
    // Clean up all dynamically allocated Person objects
    for (Person* p : usersList) {
        delete p;
    }
    usersList.clear();

    // Clean up all dynamically allocated Course objects
    for (Course* c : coursesList) {
        delete c;
    }
    coursesList.clear();

    std::cout << "[System] Memory cleanup complete. Shutting down safely.\n";
}

void RegistrationSystem::loadSystemData() {
    std::cout << "--- BOOTING SYSTEM: LOADING DATA ---\n";

    usersList = userRepo.loadAll();
    coursesList = courseRepo.loadAll();

    // Include hardcoded Admin to prevent lockdown
    usersList.push_back(new Administrator("A001", "Admin Kaveesha"));

    std::cout << "[System] Successfully loaded " << usersList.size() << " users and " 
              << coursesList.size() << " courses into memory.\n";
}

void RegistrationSystem::saveSystemData() {
    userRepo.saveAll(usersList);
    courseRepo.saveAll(coursesList);
}

const std::vector<Course*>& RegistrationSystem::getCourses() const {
    return coursesList;
}

Course* RegistrationSystem::findCourse(const std::string& courseCode) const {
    for (Course* c : coursesList) {
        if (c->getCourseCode() == courseCode) {
            return c;
        }
    }
    return nullptr;
}

Person* RegistrationSystem::loginUser() {
    std::string inputID;
    
    while (true) {
        std::cout << "\n=========================================\n";
        std::cout << "  UNIVERSITY REGISTRATION SYSTEM LOGIN\n";
        std::cout << "=========================================\n";
        std::cout << "Enter User ID ('exit' to shutdown, 'test' for diagnostics): ";
        std::cin >> inputID;

        if (inputID == "exit") {
            return nullptr; 
        }

        // --- AUTOMATED TESTING HARNESS ---
        if (inputID == "test") {
            std::cout << "\n--- INITIATING AUTOMATED EXCEPTION TEST ---\n";
            try {
                // Instantiate the testing mechanism
                FileReplayCapture fileTest("data/test_attendance.txt");
                fileTest.beginSession();
                
                std::string capturedID;
                // Loop until End of File is reached
                while ((capturedID = fileTest.captureNext()) != "EOF") {
                    std::cout << "[Scanner] Processed ID: " << capturedID << "\n";
                }
                
                fileTest.endSession();
            } 
            catch (const CustomException& e) {
                // Prove that the system catches the error without crashing
                std::cout << "\n[SUCCESS] Engine safely intercepted malformed data!\n";
                std::cout << ">> Exception Thrown: " << e.what() << "\n";
            } 
            catch (const std::exception& e) {
                std::cout << "\n[Fatal File Error] " << e.what() << "\n";
            }
            continue; // Go back to the login prompt without crashing
        }
        // -----------------------------------------

        for (Person* user : usersList) {
            if (user->getID() == inputID) {
                std::cout << "\n[System] Authentication successful. Welcome!\n";
                return user; 
            }
        }
        
        std::cout << "[Error] User ID not found. Please try again.\n";
    }
}

void RegistrationSystem::run() {
    // Boot up and load data
    loadSystemData();
    
    // The Main Application Loop
    while (true) {
        Person* currentUser = loginUser();
        
        // If login returns nullptr, the user typed 'exit'
        if (currentUser == nullptr) {
            std::cout << "Initiating system shutdown sequence...\n";
            break; 
        }

        // The Polymorphic UI and Safety Net
        try {
            // Polymorphic routing: C++ determines the correct menu at runtime
            currentUser->displayMenu(this); 
        } 
        catch (const CustomException& e) {
            // Globally catch any business rule violations (like ClashException)
            std::cout << "\n[System Alert] " << e.what() << "\n";
        }
        catch (const std::exception& e) {
            // Failsafe for standard C++ errors
            std::cout << "\n[Fatal Error] " << e.what() << "\n";
        }
    }
}