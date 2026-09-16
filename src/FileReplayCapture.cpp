#include "FileReplayCapture.h"
#include <iostream>

FileReplayCapture::FileReplayCapture(std::string file) : filename(file) {}

void FileReplayCapture::beginSession() {
    std::cout << "[FileReplay] Beginning session from " << filename << "\n";
}

std::string FileReplayCapture::captureNext() {
    return ""; // Stub returning empty string
}

void FileReplayCapture::endSession() {
    std::cout << "[FileReplay] Ending session.\n";
}