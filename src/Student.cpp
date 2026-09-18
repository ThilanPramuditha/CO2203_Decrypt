#include "Student.h"
#include "Course.h"
#include "ProjectCourse.h"
#include "LectureCourse.h"
#include "TimetableSlot.h"
#include "CustomExceptions.h"
#include "RegistrationSystem.h"
#include <iostream>
#include <algorithm>
#include <limits> 

Student::Student(std::string id, std::string name) : Person(std::move(id), std::move(name)) {}

void Student::enrol(Course* c) {
    c->checkEligibility(this);
    
    if (personalTimetable.checkClash(c->getSchedule())) {
        throw ClashException("Timetable clash detected with an existing course.");
    }
    
    enrolledCourses.push_back(c);
    personalTimetable.addSlot(c->getSchedule());
    c->addStudent(this);
}

void Student::dropCourse(Course* c) {
    auto it = std::find(enrolledCourses.begin(), enrolledCourses.end(), c);
    if (it != enrolledCourses.end()) {
        personalTimetable.removeSlot(c->getSchedule());
        enrolledCourses.erase(it);
        c->removeStudent(this);
    }
}

bool Student::hasCompleted(Course* c) const {
    return std::find(completedCourses.begin(), completedCourses.end(), c) != completedCourses.end();
}

void Student::displayMenu(RegistrationSystem* sys) {
    std::cout << "\n--- Welcome back, " << this->getName() << "! ---\n";
    int choice = 0;
    while (choice != 5) { 
        std::cout << "\n--- Student Dashboard ---\n";
        std::cout << "1. View Enrolled Courses\n";
        std::cout << "2. Enrol in a Course\n";
        std::cout << "3. Drop a Course\n";
        std::cout << "4. View Personal Timetable\n";
        std::cout << "5. Logout\n";
        std::cout << "Enter choice: ";
        
        if (!(std::cin >> choice)) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "[ERROR] Invalid input.\n";
            continue;
        }

        switch (choice) {
            case 1:
                std::cout << "\n--- Enrolled Courses ---\n";
                if (enrolledCourses.empty()) std::cout << "No courses enrolled.\n";
                for (Course* c : enrolledCourses) {
                    std::cout << *c << "\n";
                }
                break;
                
            case 2: {
                std::cout << "\n--- Enrol in Course ---\n";
                
                const auto& courses = sys->getCourses();
                if (courses.empty()) {
                    std::cout << "No courses available in the system.\n";
                    break;
                }
                
                std::cout << "Available Courses:\n";
                for (Course* c : courses) {
                    std::cout << *c << "\n";
                }
                
                std::cout << "\nEnter Course Code to enrol: ";
                std::string code;
                std::cin >> code;
                
                Course* targetCourse = sys->findCourse(code);
                if (!targetCourse) {
                    std::cout << "[ERROR] Course not found.\n";
                    break;
                }
                
                std::cout << "Attempting to enrol " << getID() << " in " << targetCourse->getCourseCode() << "...\n";
                
                try {
                    enrol(targetCourse); 
                    std::cout << "[SUCCESS] Successfully enrolled!\n";
                } 
                catch (const CustomException& e) {
                    std::cout << "\n[BLOCKED BY SYSTEM] " << e.what() << "\n";
                }
                catch (const std::exception& e) {
                    std::cout << "\n[FATAL ERROR] " << e.what() << "\n";
                }
                break;
            }
                
            case 3: {
                std::cout << "\n--- Drop Course ---\n";
                if (enrolledCourses.empty()) {
                    std::cout << "Action Failed: You are not currently enrolled in any courses.\n";
                } else {
                    std::cout << "Enter Course Code to drop: ";
                    std::string code;
                    std::cin >> code;
                    
                    Course* targetCourse = sys->findCourse(code);
                    if (!targetCourse) {
                        std::cout << "[ERROR] Course not found in system.\n";
                        break;
                    }
                    
                    auto it = std::find(enrolledCourses.begin(), enrolledCourses.end(), targetCourse);
                    if (it == enrolledCourses.end()) {
                        std::cout << "[ERROR] You are not enrolled in " << code << ".\n";
                        break;
                    }
                    
                    try {
                        dropCourse(targetCourse);
                        std::cout << "[SUCCESS] Course " << code << " dropped successfully.\n";
                    } 
                    catch (const CustomException& e) {
                        std::cout << "\n[BLOCKED BY SYSTEM] " << e.what() << "\n";
                    }
                    catch (const std::exception& e) {
                        std::cout << "\n[FATAL ERROR] " << e.what() << "\n";
                    }
                }
                break;
            }
                
            case 4:
                std::cout << "\n--- Personal Timetable ---\n";
                std::cout << personalTimetable << "\n";
                break;
                
            case 5:
                std::cout << "Logging out...\n";
                break;
                
            default:
                std::cout << "[ERROR] Invalid choice.\n";
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << "Student," << s.getID();
    return os;
}