#include "RegistrationSystem.h"
#include <iostream>

// Initialize the file paths via the constructor initialization list
RegistrationSystem::RegistrationSystem() 
    : userRepo("data/users_data.txt"), courseRepo("data/courses_data.txt") {}

// Safely delete dynamically allocated pointers
RegistrationSystem::~RegistrationSystem() {
    for (Person* p : usersList) { delete p; }
    for (Course* c : coursesList) { delete c; }
}

void RegistrationSystem::loadSystemData() {
    std::cout << "--- BOOTING SYSTEM: LOADING DATA ---\n";
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