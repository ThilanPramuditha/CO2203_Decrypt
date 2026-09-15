#ifndef ATTENDANCE_RECORD_H
#define ATTENDANCE_RECORD_H

#include <string>

class AttendanceRecord {
private:
    std::string studentID;
    std::string sessionID;
    std::string timestamp;
    std::string status;
    std::string captureMethod;

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

    bool isImmutable() const;
};

#endif // ATTENDANCE_RECORD_H
