#include "../include/ConsoleCardReader.h"
#include <iostream>

void ConsoleCardReader::beginSession() {
    std::cout << "Card reader activated.\n";
}

std::string ConsoleCardReader::captureNext() {
    std::cout << "Tap card (type Student ID, or 'exit' to stop): ";
    std::string studentID;
    std::cin >> studentID;
    return studentID;
}

void ConsoleCardReader::endSession() {
    std::cout << "Card reader deactivated.\n";
}
