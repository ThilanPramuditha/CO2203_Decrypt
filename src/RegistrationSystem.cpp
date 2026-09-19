#include "RegistrationSystem.h"
#include <iostream>
#include <algorithm>
#include "Student.h"
#include "Lecturer.h"
#include "Administrator.h"
#include "LectureCourse.h"
#include "LabCourse.h"
#include "ProjectCourse.h"
#include "TimetableSlot.h"
#include "CustomExceptions.h"
#include "FileReplayCapture.h"

RegistrationSystem::RegistrationSystem() 
    : userRepo("data/users_data.csv"), courseRepo("data/courses_data.csv") {}

RegistrationSystem::~RegistrationSystem() {
    for (Person* p : usersList) {
        delete p;
    }
    usersList.clear();

    for (Course* c : coursesList) {
        delete c;
    }
    coursesList.clear();

    std::cout << "[System] Memory cleanup complete. Shutting down safely.\n";
}

void RegistrationSystem::loadSystemData() {
    std::cout << "--- BOOTING SYSTEM: LOADING DATA ---\n";

    try {
        usersList = userRepo.loadAll();
    } catch (const CustomException& e) {
        std::cout << "[System Warning] " << e.what() << "\n";
    }

    try {
        coursesList = courseRepo.loadAll();
    } catch (const CustomException& e) {
        std::cout << "[System Warning] " << e.what() << "\n";
    }


    std::ifstream enrolIn("data/enrolments_data.csv");
    if (enrolIn.is_open()) {
        std::string line;
        while (std::getline(enrolIn, line)) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string studentID, courseCode;
            std::getline(ss, studentID, ',');
            std::getline(ss, courseCode, ',');
            
            Student* targetStudent = nullptr;
            for (Person* p : usersList) {
                if (p->getID() == studentID) {
                    if (p->getRole() == "Student") {
                        targetStudent = static_cast<Student*>(p);
                    }
                    break;
                }
            }
            
            Course* targetCourse = findCourse(courseCode);
            
            if (targetStudent && targetCourse) {
                try {
                    targetStudent->enrol(targetCourse);
                } catch (...) {
                }
            }
        }
        enrolIn.close();
    }
    
    std::ifstream attIn("data/attendance_data.csv");
    if (attIn.is_open()) {
        std::string line;
        while (std::getline(attIn, line)) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string cCode, sID, sessID, timestamp, status, method;
            std::getline(ss, cCode, ',');
            std::getline(ss, sID, ',');
            std::getline(ss, sessID, ',');
            std::getline(ss, timestamp, ',');
            std::getline(ss, status, ',');
            std::getline(ss, method, ',');
            
            Course* targetCourse = findCourse(cCode);
            if (targetCourse) {
                targetCourse->getRegister()->restoreSession(sessID);
                AttendanceRecord record(sID, sessID, timestamp, status, method);
                try {
                    targetCourse->getRegister()->addRecord(record);
                } catch (...) {
                }
            }
        }
        attIn.close();
    }
    
    for (Course* c : coursesList) {
        std::string supID = c->getSupervisorID();
        if (!supID.empty()) {
            for (Person* p : usersList) {
                if (p->getID() == supID) {
                    if (Lecturer* l = dynamic_cast<Lecturer*>(p)) {
                        l->addTaughtCourse(c);
                    }
                    break;
                }
            }
        }
    }

    std::cout << "[System] Successfully loaded " << usersList.size() << " users and " 
              << coursesList.size() << " courses into memory.\n";
}

void RegistrationSystem::saveSystemData() {
    userRepo.saveAll(usersList);
    courseRepo.saveAll(coursesList);
    
    std::ofstream enrolOut("data/enrolments_data.csv");
    if (enrolOut.is_open()) {
        for (Person* p : usersList) {
            if (p->getRole() == "Student") {
                Student* s = static_cast<Student*>(p);
                for (Course* c : s->getEnrolledCourses()) {
                    enrolOut << s->getID() << "," << c->getCourseCode() << "\n";
                }
            }
        }
        enrolOut.close();
    }
    
    std::ofstream attOut("data/attendance_data.csv");
    if (attOut.is_open()) {
        for (Course* c : coursesList) {
            for (const AttendanceRecord& record : c->getRegister()->getRecords()) {
                attOut << c->getCourseCode() << ","
                       << record.getStudentID() << ","
                       << record.getSessionID() << ","
                       << record.getTimestamp() << ","
                       << record.getStatus() << ","
                       << record.getCaptureMethod() << "\n";
            }
        }
        attOut.close();
    }
}

const std::vector<Person*>& RegistrationSystem::getUsers() const {
    return usersList;
}

const std::vector<Course*>& RegistrationSystem::getCourses() const {
    return coursesList;
}

void RegistrationSystem::addUser(Person* user) {
    usersList.push_back(user);
}

void RegistrationSystem::addCourse(Course* course) {
    coursesList.push_back(course);
}

void RegistrationSystem::removeUser(const std::string& userID) {
    auto it = std::find_if(usersList.begin(), usersList.end(), [&](Person* p) { return p->getID() == userID; });
    if (it != usersList.end()) {
        delete *it;
        usersList.erase(it);
        std::cout << "[System] User " << userID << " successfully removed.\n";
    } else {
        std::cout << "[ERROR] User not found.\n";
    }
}

void RegistrationSystem::removeCourse(const std::string& courseCode) {
    auto it = std::find_if(coursesList.begin(), coursesList.end(), [&](Course* c) { return c->getCourseCode() == courseCode; });
    if (it != coursesList.end()) {
        delete *it;
        coursesList.erase(it);
        std::cout << "[System] Course " << courseCode << " successfully removed.\n";
    } else {
        std::cout << "[ERROR] Course not found.\n";
    }
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
        std::cout << "Enter User ID ('exit' to shutdown): ";
        if (!(std::cin >> inputID)) {
            std::cout << "\n[System] Input stream closed. Shutting down.\n";
            return nullptr;
        }

        std::string lowerInput = inputID;
        for (char& c : lowerInput) c = std::tolower(c);

        if (lowerInput == "exit") {
            return nullptr; 
        }

        for (char& c : inputID) c = std::toupper(c);

        if (inputID == "TEST") {
            std::cout << "\n--- INITIATING AUTOMATED EXCEPTION TEST ---\n";
            FileReplayCapture fileTest("data/test_attendance.txt");
            fileTest.beginSession();
            
            while (true) {
                try {
                    std::string capturedID = fileTest.captureNext();
                    if (capturedID == "EOF") break;
                    std::cout << "[Scanner] Processed ID: " << capturedID << "\n";
                } 
                catch (const CustomException& e) {
                    std::cout << "\n[SUCCESS] Engine safely intercepted malformed data!\n";
                    std::cout << ">> Exception Thrown: " << e.what() << "\n";
                } 
                catch (const std::exception& e) {
                    std::cout << "\n[Fatal File Error] " << e.what() << "\n";
                    break;
                }
            }
            
            fileTest.endSession();
            continue;
        }

        for (Person* user : usersList) {
            if (user->getID() == inputID) {
                std::cout << "\n[System] Authentication successful. Welcome!\n";
                if (user->getRole() == "Administrator") {
                    static_cast<Administrator*>(user)->setSystem(this);
                }
                return user; 
            }
        }
        
        std::cout << "[Error] User ID not found. Please try again.\n";
    }
}

void RegistrationSystem::run() {
    loadSystemData();
    
    while (true) {
        Person* currentUser = loginUser();
        
        if (currentUser == nullptr) {
            std::cout << "Initiating system shutdown sequence...\n";
            saveSystemData();
            break; 
        }

        try {
            currentUser->displayMenu(this); 
        } 
        catch (const CustomException& e) {
            std::cout << "\n[System Alert] " << e.what() << "\n";
        }
        catch (const std::exception& e) {
            std::cout << "\n[Fatal Error] " << e.what() << "\n";
        }
    }
}