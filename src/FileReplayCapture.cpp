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
    
    if (!replayStream.is_open()) {
        throw std::runtime_error("Critical Error: Missing replay file at " + filename);
    }
    std::cout << "[FileReplay] Automated session started. Reading from " << filename << "...\n";
}

std::string FileReplayCapture::captureNext() {
    if (!replayStream.is_open()) {
        return "EOF";
    }

    std::string line;
    if (std::getline(replayStream, line)) {
        if (line.empty() || line == "MALFORMED_DATA" || line == "ERROR_STUB") {
            throw CustomException("Malformed attendance event detected in replay file.");
        }
        return line;
    }

    return "EOF";
}

void FileReplayCapture::endSession() {
    if (replayStream.is_open()) {
        replayStream.close();
    }
    std::cout << "[FileReplay] Automated session ended. Stream safely closed.\n";
}