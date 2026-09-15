#ifndef ATTENDANCE_CAPTURE_H
#define ATTENDANCE_CAPTURE_H

#include <string>

// ==========================================
// STRATEGY PATTERN - the "Strategy" interface.
// AttendanceSession holds a pointer to one of these (composition-by-
// reference / aggregation) and delegates the actual work of capturing
// attendance to whichever concrete strategy is plugged in at runtime
// (file replay, console card reader, QR code, etc.) without needing
// to know which one it is.
// ==========================================
class AttendanceCapture {
public:
    virtual ~AttendanceCapture() = default;

    // Called once when a session starts capturing attendance
    // (e.g. open a file, initialise a reader, generate a token).
    virtual void beginSession() = 0;

    // Called repeatedly to pull the next captured student ID.
    // Returns an empty string when there is nothing left to capture.
    virtual std::string captureNext() = 0;

    // Called once when the session is finished capturing
    // (e.g. close a file handle, release a reader).
    virtual void endSession() = 0;
};

#endif // ATTENDANCE_CAPTURE_H
