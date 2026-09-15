#ifndef FILE_REPLAY_CAPTURE_H
#define FILE_REPLAY_CAPTURE_H

#include "AttendanceCapture.h"

// ==========================================
// Concrete strategy: replays previously recorded attendance
// swipes/scans from a flat file. Useful for testing/demo data
// without needing real hardware.
// ==========================================
class FileReplayCapture : public AttendanceCapture {
private:
    std::string filename;

public:
    explicit FileReplayCapture(const std::string& filename);

    void beginSession() override;
    std::string captureNext() override;
    void endSession() override;
};

#endif // FILE_REPLAY_CAPTURE_H
