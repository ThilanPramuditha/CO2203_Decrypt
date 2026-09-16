#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include <string>
#include <iostream>

template <typename T>
class Repository {
private:
    std::string filePath;

public:
    // Constructor initializes the target file path
    Repository(std::string path) : filePath(path) {}

    // Generic method to serialize a vector of object pointers into a file
    void saveAll(const std::vector<T*>& entities) {
        // Stub for File I/O implementation
        std::cout << "[Repository] Saving data to " << filePath << "...\n";
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
