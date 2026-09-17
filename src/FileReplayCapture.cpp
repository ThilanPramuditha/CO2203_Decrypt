#include "FileReplayCapture.h"
#include "CustomExceptions.h"
#include <iostream>
#include <stdexcept>
#include <utility>

FileReplayCapture::FileReplayCapture(std::string file) : filename(std::move(file)) {}

FileReplayCapture::~FileReplayCapture() {
    if (replayStream.is_open()) {
        replayStream.close();
    }
}

void FileReplayCapture::beginSession() {
    replayStream.open(filename);
    
    // Graceful exception handling for missing data files
    if (!replayStream.is_open()) {
        throw std::runtime_error("Critical Error: Missing replay file at " + filename);
    }
    std::cout << "[FileReplay] Automated session started. Reading from " << filename << "...\n";
}

std::string FileReplayCapture::captureNext() {
    if (!replayStream.is_open()) {
        return "EOF"; // Signals the attendance engine to stop
    }

    std::string line;
    if (std::getline(replayStream, line)) {
        // Testing boundary failure modes and malformed lines
        if (line.empty() || line == "MALFORMED_DATA" || line == "ERROR_STUB") {
            // Throw our team's CustomException to prove the system gracefully catches errors without crashing
            throw CustomException("Malformed attendance event detected in replay file.");
        }
        return line; // Returns the valid student ID
    }

    return "EOF"; // End of file reached
}

void FileReplayCapture::endSession() {
    if (replayStream.is_open()) {
        replayStream.close();
    }
    std::cout << "[FileReplay] Automated session ended. Stream safely closed.\n";
}