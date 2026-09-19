#include "QRCodeCapture.h"
#include "qrcodegen.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>

#ifdef _WIN32
#include <windows.h>
#endif
using namespace qrcodegen;

void QRCodeCapture::beginSession() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::time_t now = std::time(nullptr);
    sessionStartTime = now;
    int randomPart = std::rand() % 9000 + 1000;
    
    sessionToken = "TOKEN-SESSION1-" + std::to_string(now) + "-" + std::to_string(randomPart);
    
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    std::cout << "QR session started.\n";
    
    try {
        QrCode qr = QrCode::encodeText(sessionToken.c_str(), QrCode::Ecc::MEDIUM);
        
        for (int x = 0; x < qr.getSize() + 4; x++) std::cout << "  ";
        std::cout << "\n";
        
        for (int y = 0; y < qr.getSize(); y++) {
            std::cout << "    ";
            for (int x = 0; x < qr.getSize(); x++) {
                std::cout << (qr.getModule(x, y) ? "██" : "  ");
            }
            std::cout << "    \n";
        }
        
        for (int x = 0; x < qr.getSize() + 4; x++) std::cout << "  ";
        std::cout << "\n";
        
    } catch (const std::exception& e) {
        std::cout << "[ERROR] Failed to generate QR code: " << e.what() << "\n";
    }
}

std::string QRCodeCapture::captureNext() {
    while (true) {
        std::cout << "\nEnter decoded QR Token (or 'exit' to stop): ";
        std::string tokenInput;
        if (!(std::cin >> tokenInput)) return "exit";
        
        if (std::difftime(std::time(nullptr), sessionStartTime) > 120) {
            std::cout << "[ERROR] QR Code has expired. Session closed.\n";
            return "exit";
        }
        
        std::string lowerToken = tokenInput;
        for (char& c : lowerToken) c = std::tolower(c);
        
        if (lowerToken == "exit" || tokenInput.empty()) {
            return "exit";
        }
        
        if (tokenInput == sessionToken) {
            std::cout << "Token Validated! Enter Student ID: ";
            std::string studentID;
            if (!(std::cin >> studentID)) return "exit";
            return studentID;
        } else {
            std::cout << "[ERROR] Invalid or expired token. Please scan the active QR code.\n";
        }
    }
}

void QRCodeCapture::endSession() {
    std::cout << "QR session closed.\n";
}
