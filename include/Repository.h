#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>     
#include <stdexcept>   
#include <type_traits> 
#include "Person.h"
#include "Student.h"
#include "Course.h"
#include "LectureCourse.h"


template <typename T>
class Repository {
private:
    std::string filePath;

public:
    Repository(std::string path) : filePath(path) {}

    void saveAll(const std::vector<T*>& entities) {
        std::ofstream outFile(filePath);
        if (!outFile.is_open()) {
            std::cerr << "[Repository Error] Could not open file: " << filePath << "\n";
            return;
        }
        
        std::cout << "[Repository] Saving " << entities.size() << " records to " << filePath << "...\n";
        for (const T* entity : entities) {
            if constexpr (std::is_same_v<T, Person>) {
                if (const Student* s = dynamic_cast<const Student*>(entity)) {
                    outFile << *s << "\n";
                } else {
                    std::cout << "[Repository] Stub: Saving non-student Person to " << filePath << "...\n";
                }
            } else {
                outFile << *entity << "\n"; 
            }
        }
        outFile.close();
    }

    std::vector<T*> loadAll() {
        std::vector<T*> loadedEntities;
        std::ifstream inFile(filePath);

        // Graceful error handling for missing files
        if (!inFile.is_open()) {
            throw std::runtime_error("Critical Error: Missing or corrupt data file at " + filePath);
        }

        std::string line;
        std::cout << "[Repository] Loading data from " << filePath << "...\n";

        while (std::getline(inFile, line)) {
            if (line.empty()) continue; 

            std::stringstream ss(line);
            std::string typeToken;
            
            // Read the first column to determine the specific derived class
            std::getline(ss, typeToken, ','); 

            // 1. Person Hierarchy Reconstruction
            if constexpr (std::is_same_v<T, Person>) {
                if (typeToken == "Student") {
                    std::string id;
                    std::getline(ss, id, ',');
                    std::string name = "Unknown";
                    
                    loadedEntities.push_back(new Student(id, name));
                }
            }
            
            // 2. Course Hierarchy Reconstruction
            else if constexpr (std::is_same_v<T, Course>) {
                if (typeToken == "LectureCourse") {
                    std::string code, title, capacityStr;
                    std::getline(ss, code, ',');
                    std::getline(ss, title, ',');
                    std::getline(ss, capacityStr, ',');
                    
                    int cap = capacityStr.empty() ? 0 : std::stoi(capacityStr);
                    TimetableSlot dummySlot(1, 800, 1000, "Unknown");
                    
                    loadedEntities.push_back(new LectureCourse(code, title, cap, dummySlot));
                }
            }
        }

        inFile.close();
        return loadedEntities; 
    }
};

#endif // REPOSITORY_H