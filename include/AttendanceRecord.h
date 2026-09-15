#ifndef ATTENDANCE_RECORD_H
#define ATTENDANCE_RECORD_H

#include <string>

// ==========================================
// A single, immutable attendance entry: "this student was marked
// present/absent/late at this timestamp, via this capture method".
// Immutable by convention -- corrections are appended separately
// as CorrectionRecord objects rather than editing this record.
// ==========================================
class AttendanceRecord {
private:
    std::string studentID;
    std::string sessionID;
    std::string timestamp;
    std::string status;         // e.g. "PRESENT", "ABSENT", "LATE"
    std::string captureMethod;  // e.g. "QRCode", "ConsoleCardReader"

public:
    AttendanceRecord(const std::string& studentID,
                      const std::string& sessionID,
                      const std::string& timestamp,
                      const std::string& status,
                      const std::string& captureMethod);

    std::string getStudentID() const;
    std::string getSessionID() const;
    std::string getTimestamp() const;
    std::string getStatus() const;
    std::string getCaptureMethod() const;

    // Always returns true; records are never mutated in place.
    bool isImmutable() const;
};

#endif // ATTENDANCE_RECORD_H
