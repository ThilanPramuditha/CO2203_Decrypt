#include "QRCodeCapture.h"
#include "qrcodegen.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#endif
using namespace qrcodegen;

void QRCodeCapture::beginSession() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::time_t now = std::time(nullptr);
    sessionStartTime = now;
    int randomPart = std::rand() % 9000 + 1000;
    
    // 1. Dynamic Token Generation (Session ID + Expiry + Hash)
    sessionToken = "TOKEN-SESSION1-" + std::to_string(now) + "-" + std::to_string(randomPart);
    
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    std::cout << "QR session started.\n";
    
    // 2. Library Integration: Encode and print the ASCII QR Code
    try {
        QrCode qr = QrCode::encodeText(sessionToken.c_str(), QrCode::Ecc::MEDIUM);
        
        // Print top border for padding
        for (int x = 0; x < qr.getSize() + 4; x++) std::cout << "  ";
        std::cout << "\n";
        
        for (int y = 0; y < qr.getSize(); y++) {
            std::cout << "    "; // Left border padding
            for (int x = 0; x < qr.getSize(); x++) {
                // Using standard extended ASCII block characters for the QR code
                std::cout << (qr.getModule(x, y) ? "██" : "  ");
            }
            std::cout << "    \n"; // Right border padding
        }
        
        // Print bottom border for padding
        for (int x = 0; x < qr.getSize() + 4; x++) std::cout << "  ";
        std::cout << "\n";
        
    } catch (const std::exception& e) {
        std::cout << "[ERROR] Failed to generate QR code: " << e.what() << "\n";
    }
}

std::string QRCodeCapture::captureNext() {
    // 3. Validation: Prompt for decoded payload
    while (true) {
        std::cout << "\nEnter decoded QR Token (or 'exit' to stop): ";
        std::string tokenInput;
        std::getline(std::cin, tokenInput);
        
        if (std::difftime(std::time(nullptr), sessionStartTime) > 60) {
            std::cout << "[ERROR] QR Code has expired. Session closed.\n";
            return "exit";
        }
        
        if (tokenInput == "exit" || tokenInput.empty()) {
            return "exit";
        }
        
        if (tokenInput == sessionToken) {
            std::cout << "Token Validated! Enter Student ID: ";
            std::string studentID;
            std::getline(std::cin, studentID);
            return studentID;
        } else {
            std::cout << "[ERROR] Invalid or expired token. Please scan the active QR code.\n";
        }
    }
}

void QRCodeCapture::endSession() {
    std::cout << "QR session closed.\n";
}
