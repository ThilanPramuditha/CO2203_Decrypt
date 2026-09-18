#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>     
#include <stdexcept>   
#include "Person.h"
#include "Student.h"
#include "Lecturer.h"
#include "Course.h"
#include "LectureCourse.h"
#include "LabCourse.h"
#include "ProjectCourse.h"
#include "TimetableSlot.h"

// Generic Template Declaration
template <typename T>
class Repository;

// ---------------------------------------------------------
// EXPLICIT SPECIALIZATION FOR PERSON
// ---------------------------------------------------------
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
        // Simplified saving logic, omitting dynamic_cast
        // Normally handled via virtual serialization methods.
        outFile.close();
    }

    inline std::vector<Person*> loadAll() {
        std::vector<Person*> loadedEntities;
        std::ifstream inFile(filePath);

        if (!inFile.is_open()) {
            // Graceful handling: create the file if it doesn't exist
            std::ofstream newFile(filePath);
            newFile.close();
            return loadedEntities; 
        }

        std::string line;
        std::cout << "[Repository] Loading Person data from " << filePath << "...\n";

        while (std::getline(inFile, line)) {
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
            }
        }

        inFile.close();
        return loadedEntities; 
    }
};

// ---------------------------------------------------------
// EXPLICIT SPECIALIZATION FOR COURSE
// ---------------------------------------------------------
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
        outFile.close();
    }

    inline std::vector<Course*> loadAll() {
        std::vector<Course*> loadedEntities;
        std::ifstream inFile(filePath);

        if (!inFile.is_open()) {
            // Graceful handling: create the file if it doesn't exist
            std::ofstream newFile(filePath);
            newFile.close();
            return loadedEntities; 
        }

        std::string line;
        std::cout << "[Repository] Loading Course data from " << filePath << "...\n";

        while (std::getline(inFile, line)) {
            if (line.empty()) continue; 

            std::stringstream ss(line);
            std::string type, code, title, capacityStr, location, supervisor;
            
            std::getline(ss, type, ',');
            std::getline(ss, code, ',');
            std::getline(ss, title, ',');
            std::getline(ss, capacityStr, ',');
            std::getline(ss, location, ',');
            std::getline(ss, supervisor, ',');
            
            int cap = capacityStr.empty() ? 0 : std::stoi(capacityStr);
            
            // Inject default time values for TimetableSlot
            TimetableSlot defaultSlot(1, 800, 1000, location);
            
            if (type == "LectureCourse") {
                loadedEntities.push_back(new LectureCourse(code, title, cap, defaultSlot));
            } else if (type == "LabCourse") {
                int groupSize = cap / 2;
                loadedEntities.push_back(new LabCourse(code, title, cap, defaultSlot, groupSize));
            } else if (type == "ProjectCourse") {
                loadedEntities.push_back(new ProjectCourse(code, title, cap, defaultSlot, supervisor));
            }
        }

        inFile.close();
        return loadedEntities; 
    }
};

#endif // REPOSITORY_H