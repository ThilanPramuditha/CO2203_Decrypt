#ifndef FILE_REPLAY_CAPTURE_H
#define FILE_REPLAY_CAPTURE_H

#include "AttendanceCapture.h"
#include <string>

// Derived class used for bulk-testing the system via text files
class FileReplayCapture : public AttendanceCapture {
private:
    std::string filename;

public:
    FileReplayCapture(std::string file);

    void beginSession() override;
    std::string captureNext() override;
    void endSession() override;
};

#endif // FILE_REPLAY_CAPTURE_H