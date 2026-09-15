#include "Administrator.h"
#include <iostream>

Administrator::Administrator(std::string id, std::string name) : Person(std::move(id), std::move(name)) {}

void Administrator::createUser() { std::cout << "Creating new user...\n"; }
void Administrator::updateUser(std::string userID) { std::cout << "Updating user...\n"; }
void Administrator::removeUser(std::string userID) { std::cout << "Removing user...\n"; }
void Administrator::createCourse() { std::cout << "Creating new course...\n"; }
void Administrator::editCourse(std::string courseCode) { std::cout << "Editing course...\n"; }
void Administrator::removeCourse(std::string courseCode) { std::cout << "Removing course...\n"; }
void Administrator::generateReport() { std::cout << "Generating system report...\n"; }

void Administrator::displayMenu() {
    std::cout << "--- Administrator Dashboard ---\n";
    std::cout << "1. Manage Users\n";
    std::cout << "2. Manage Courses\n";
    std::cout << "3. System Reports\n";
}