#ifndef FILE_REPLAY_CAPTURE_H
#define FILE_REPLAY_CAPTURE_H

#include "AttendanceCapture.h"
#include <string>
#include <fstream> // Required to maintain the file stream state

class FileReplayCapture : public AttendanceCapture {
private:
    std::string filename;
    std::ifstream replayStream; // Private state variable to keep the file open during the session

public:
    FileReplayCapture(std::string file);
    
    // Virtual destructor ensures proper cleanup of derived objects
    ~FileReplayCapture() override; 

    // Implementing the pure virtual functions from the abstract base class
    void beginSession() override;
    std::string captureNext() override;
    void endSession() override;
};

#endif // FILE_REPLAY_CAPTURE_H