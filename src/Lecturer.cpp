#include "Lecturer.h"
#include <iostream>

Lecturer::Lecturer(std::string id, std::string name) : Person(std::move(id), std::move(name)) {}

void Lecturer::openSession(Course* c) {
    std::cout << "Opening session for course...\n";
}

void Lecturer::closeSession(std::string sessionID) {
    std::cout << "Closing session: " << sessionID << "\n";
}

void Lecturer::displayMenu() {
    std::cout << "--- Lecturer Dashboard ---\n";
    std::cout << "1. Open Attendance Session\n";
    std::cout << "2. Close Attendance Session\n";
}