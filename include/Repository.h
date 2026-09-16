#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream> // REQUIRED FOR FILE I/O

template <typename T>
class Repository {
private:
    std::string filePath;

public:
    // Constructor initializes the target file path
    Repository(std::string path) : filePath(path) {}

    // Generic method to serialize a vector of object pointers into a file
    void saveAll(const std::vector<T*>& entities) {
        // Open the file in output mode
        std::ofstream outFile(filePath);
        
        if (!outFile.is_open()) {
            std::cerr << "[Repository Error] Could not open file: " << filePath << "\n";
            return;
        }

        std::cout << "[Repository] Saving " << entities.size() << " records to " << filePath << "...\n";
        
        // Loop through all pointers and write them to the file
        for (const T* entity : entities) {
            outFile << *entity << "\n"; 
        }
        
        outFile.close();
    }

    // Generic method to read a file and reconstruct object pointers
    std::vector<T*> loadAll() {
        std::vector<T*> loadedEntities;
        // Stub for File I/O implementation
        std::cout << "[Repository] Loading data from " << filePath << "...\n";
        return loadedEntities; 
    }
};

#endif // REPOSITORY_H