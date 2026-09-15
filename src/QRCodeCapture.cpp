#include "../include/QRCodeCapture.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

void QRCodeCapture::beginSession() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    sessionToken = "QR-" + std::to_string(std::rand() % 900000 + 100000);
    std::cout << "QR session started. Token: " << sessionToken << "\n";
}

std::string QRCodeCapture::captureNext() {
    std::cout << "Scan QR " << sessionToken << " -> enter Student ID (or 'exit' to stop): ";
    std::string studentID;
    std::getline(std::cin, studentID);
    return studentID;
}

void QRCodeCapture::endSession() {
    std::cout << "QR session " << sessionToken << " closed.\n";
}
