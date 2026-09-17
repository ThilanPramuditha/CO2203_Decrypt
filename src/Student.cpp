#include "Student.h"
#include "Course.h"
#include "ProjectCourse.h"
#include "LectureCourse.h"
#include "TimetableSlot.h"
#include "CustomExceptions.h"
#include <iostream>
#include <algorithm>
#include <limits> 

Student::Student(std::string id, std::string name) : Person(std::move(id), std::move(name)) {}

void Student::enrol(Course* c) {
    if (!c->isEligible(this)) {
        throw CustomException("Student failed eligibility checks for this course.");
    }
    
    if (personalTimetable.checkClash(c->getSchedule())) {
        throw ClashException("Timetable clash detected with an existing course.");
    }
    
    enrolledCourses.push_back(c);
    personalTimetable.addSlot(c->getSchedule());
}

void Student::dropCourse(Course* c) {
    auto it = std::find(enrolledCourses.begin(), enrolledCourses.end(), c);
    if (it != enrolledCourses.end()) {
        enrolledCourses.erase(it);
    }
}

bool Student::hasCompleted(Course* c) const {
    return std::find(completedCourses.begin(), completedCourses.end(), c) != completedCourses.end();
}

void Student::displayMenu() {
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
                std::cout << "Attempting to enrol S001 in CO2307 (Project Course)...\n";
                
                // Create a dummy course to test the exception limits
                TimetableSlot dummySlot(3, 1400, 1600, "Hall A");
                ProjectCourse testCourse("CO2307", "Software Engineering Project", 50, dummySlot, "L001");
                
                // Add a dummy prerequisite that S001 has not completed
                LectureCourse prereqCourse("CO1101", "Programming Foundations", 100, dummySlot);
                testCourse.addPrerequisite(&prereqCourse);
                
                // Wrap the enrol() function in a try/catch block
                try {
                    enrol(&testCourse); 
                    std::cout << "[SUCCESS] Successfully enrolled!\n";
                } 
                catch (const CustomException& e) {
                    // Catches the domain error without crashing the terminal
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
                    // Automatically grab the last enrolled course and safely drop it
                    Course* c = enrolledCourses.back();
                    std::cout << "Dropping most recent course...\n";
                    try {
                        dropCourse(c);
                        std::cout << "[SUCCESS] Course dropped successfully.\n";
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

// FIX: Enforced strict CSV formatting for File I/O
std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << "Student," << s.getID();
    return os;
}