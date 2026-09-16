#include "RegistrationSystem.h"
#include <iostream>
#include "Student.h"
#include "Lecturer.h"
#include "Administrator.h"
#include "LectureCourse.h"
#include "LabCourse.h"
#include "ProjectCourse.h"
#include "TimetableSlot.h"

// Initialize the file paths via the constructor initialization list
RegistrationSystem::RegistrationSystem() 
    : userRepo("data/users_data.txt"), courseRepo("data/courses_data.txt") {}

// Safely delete dynamically allocated pointers
RegistrationSystem::~RegistrationSystem() {
    for (Person* p : usersList) { delete p; }
    for (Course* c : coursesList) { delete c; }
}

void RegistrationSystem::loadSystemData() {
    std::cout << "--- BOOTING SYSTEM: LOADING MOCK DATA ---\n";

    // 1. Generate Mock Users
    usersList.push_back(new Student("S001", "Thilan Pramuditha"));
    usersList.push_back(new Student("S002", "Didula Dissanayake"));
    usersList.push_back(new Lecturer("L001", "Dr. Udaya Wijenayake"));
    usersList.push_back(new Administrator("A001", "Admin Kaveesha"));

    // 2. Generate Mock Timetable Slots (Day, StartTime, EndTime, Location)
    TimetableSlot slot1(1, 800, 1000, "Hall L5301");  // Monday 8:00 AM - 10:00 AM
    TimetableSlot slot2(2, 1000, 1200, "AI Lab");  // Tuesday 10:00 AM - 12:00 PM
    TimetableSlot slot3(3, 1400, 1600, "Hall L221A"); // Wednesday 2:00 PM - 4:00 PM

    // 3. Generate Mock Courses
    // LectureCourse: Code, Title, Capacity, Schedule
    coursesList.push_back(new LectureCourse("CO2203", "Intro to OOP", 150, slot1));
    
    // LabCourse: Code, Title, Capacity, Schedule, LabGroupSize
    coursesList.push_back(new LabCourse("CO2203-L", "OOP Lab", 30, slot2, 15));
    
    // ProjectCourse: Code, Title, Capacity, Schedule, SupervisorID
    coursesList.push_back(new ProjectCourse("CO2307", "Software Engineering Project", 50, slot3, "L001"));

    std::cout << "[System] Successfully loaded " << usersList.size() << " users and " 
              << coursesList.size() << " courses into memory.\n";
}

void RegistrationSystem::saveSystemData() {
    userRepo.saveAll(usersList);
    courseRepo.saveAll(coursesList);
}

void RegistrationSystem::run() {
    loadSystemData();
    std::cout << "System Engine is now running. Waiting for UI integration...\n";
}

Person* RegistrationSystem::loginUser() {
    return nullptr; // Stub for login routing
}