#ifndef FILE_REPLAY_CAPTURE_H
#define FILE_REPLAY_CAPTURE_H

#include "AttendanceCapture.h"
#include <string>
#include <fstream>

class FileReplayCapture : public AttendanceCapture {
private:
    std::string filename;
    std::ifstream replayStream;

public:
    FileReplayCapture(std::string file);
    
    ~FileReplayCapture() override; 

    void beginSession() override;
    std::string captureNext() override;
    void endSession() override;
    std::string getCaptureMethod() const override { return "FileReplayCapture"; }
};

#endif
