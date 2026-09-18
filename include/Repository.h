#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>     
#include <stdexcept>   
#include <iomanip>
#include "Person.h"
#include "Student.h"
#include "Lecturer.h"
#include "Administrator.h"
#include "Course.h"
#include "LectureCourse.h"
#include "LabCourse.h"
#include "ProjectCourse.h"
#include "TimetableSlot.h"

template <typename T>
class Repository;

template <>
class Repository<Person> {
private:
    std::string filePath;

public:
    Repository(std::string path) : filePath(path) {}

    inline void saveAll(const std::vector<Person*>& entities) {
        std::ofstream outFile(filePath);
        if (!outFile.is_open()) {
            std::cerr << "[Repository Error] Could not open file: " << filePath << "\n";
            return;
        }
        
        std::cout << "[Repository] Saving " << entities.size() << " records to " << filePath << "...\n";
        
        for (const Person* entity : entities) {
            outFile << entity->getRole() << "," << entity->getID() << "," << entity->getName() << "\n";
        }
        
        outFile.close();
    }

    inline std::vector<Person*> loadAll() {
        std::vector<Person*> loadedEntities;
        std::ifstream inFile(filePath);

        if (!inFile.is_open()) {
            std::ofstream newFile(filePath);
            newFile.close();
            return loadedEntities; 
        }

        std::string line;
        std::cout << "[Repository] Loading Person data from " << filePath << "...\n";

        while (std::getline(inFile, line)) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (line.empty()) continue; 

            std::stringstream ss(line);
            std::string role, id, name;
            
            std::getline(ss, role, ','); 
            std::getline(ss, id, ',');
            std::getline(ss, name, ',');

            if (role == "Student") {
                loadedEntities.push_back(new Student(id, name));
            } else if (role == "Lecturer") {
                loadedEntities.push_back(new Lecturer(id, name));
            } else if (role == "Administrator") {
                loadedEntities.push_back(new Administrator(id, name));
            }
        }

        inFile.close();
        return loadedEntities; 
    }
};

template <>
class Repository<Course> {
private:
    std::string filePath;

public:
    Repository(std::string path) : filePath(path) {}

    inline void saveAll(const std::vector<Course*>& entities) {
        std::ofstream outFile(filePath);
        if (!outFile.is_open()) {
            std::cerr << "[Repository Error] Could not open file: " << filePath << "\n";
            return;
        }
        
        std::cout << "[Repository] Saving " << entities.size() << " records to " << filePath << "...\n";
        for (const Course* entity : entities) {
            std::string prereq = "NONE";
            if (!entity->getPrerequisites().empty()) {
                prereq = entity->getPrerequisites()[0]->getCourseCode();
            }
            outFile << *entity << ","
                    << entity->getSchedule().getLocation() << ","
                    << entity->getSupervisorID() << ","
                    << entity->getSchedule().getDayOfWeek() << ","
                    << std::setfill('0') << std::setw(4) << entity->getSchedule().getStartTime() << ","
                    << std::setfill('0') << std::setw(4) << entity->getSchedule().getEndTime() << ","
                    << prereq << "\n";
        }
        outFile.close();
    }

    inline std::vector<Course*> loadAll() {
        std::vector<Course*> loadedEntities;
        std::ifstream inFile(filePath);

        if (!inFile.is_open()) {
            std::ofstream newFile(filePath);
            newFile.close();
            return loadedEntities; 
        }

        std::string line;
        std::cout << "[Repository] Loading Course data from " << filePath << "...\n";

        while (std::getline(inFile, line)) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (line.empty()) continue; 

            std::stringstream ss(line);
            std::string type, code, title, capacityStr, location, supervisor;
            std::string dayStr, startStr, endStr, prereqStr;
            
            std::getline(ss, type, ',');
            std::getline(ss, code, ',');
            std::getline(ss, title, ',');
            std::getline(ss, capacityStr, ',');
            std::getline(ss, location, ',');
            std::getline(ss, supervisor, ',');
            std::getline(ss, dayStr, ',');
            std::getline(ss, startStr, ',');
            std::getline(ss, endStr, ',');
            std::getline(ss, prereqStr, ',');
            
            int cap = capacityStr.empty() ? 0 : std::stoi(capacityStr);
            int day = dayStr.empty() ? 1 : std::stoi(dayStr);
            int start = startStr.empty() ? 800 : std::stoi(startStr);
            int end = endStr.empty() ? 1000 : std::stoi(endStr);
            
            TimetableSlot parsedSlot(day, start, end, location);
            
            Course* newCourse = nullptr;
            if (type == "LectureCourse") {
                newCourse = new LectureCourse(code, title, cap, parsedSlot);
            } else if (type == "LabCourse") {
                int groupSize = cap / 2;
                newCourse = new LabCourse(code, title, cap, parsedSlot, groupSize);
            } else if (type == "ProjectCourse") {
                newCourse = new ProjectCourse(code, title, cap, parsedSlot);
            }
            
            if (newCourse) {
                newCourse->setSupervisorID(supervisor);
                if (!prereqStr.empty() && prereqStr != "NONE") {
                    for (Course* prev : loadedEntities) {
                        if (prev->getCourseCode() == prereqStr) {
                            newCourse->addPrerequisite(prev);
                            break;
                        }
                    }
                }
                loadedEntities.push_back(newCourse);
            }
        }

        inFile.close();
        return loadedEntities; 
    }
};

#endif
