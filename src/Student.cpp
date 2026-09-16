#include "Student.h"
#include "Course.h"
#include "CustomExceptions.h"
#include <iostream>
#include <algorithm>
#include <limits> // Added for input validation

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
    while (choice != 5) { // Interactive menu loop
        std::cout << "\n--- Student Dashboard ---\n";
        std::cout << "1. View Enrolled Courses\n";
        std::cout << "2. Enrol in a Course\n";
        std::cout << "3. Drop a Course\n";
        std::cout << "4. View Personal Timetable\n";
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
                std::cout << "\n--- Enrolled Courses ---\n";
                if (enrolledCourses.empty()) std::cout << "No courses enrolled.\n";
                for (Course* c : enrolledCourses) {
                    std::cout << *c << "\n";
                }
                break;
            case 2:
                std::cout << "\n--- Enrol in Course ---\n";
                std::cout << "(Pending system integration)\n";
                
                // Exception handling block
                /* 
                try {
                    enrol(selectedCourse);
                } catch (const std::exception& e) {
                    std::cout << "\n[ERROR] " << e.what() << "\n";
                }
                */
                break;
            case 3:
                std::cout << "\n--- Drop Course ---\n";
                std::cout << "(Pending system integration)\n";
                break;
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
    os << "Student [ID: " << s.getID() << "]";
    return os;
}