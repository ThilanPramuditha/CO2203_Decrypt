#include "../include/AttendanceRecord.h"

AttendanceRecord::AttendanceRecord(const std::string& studentID,
                                   const std::string& sessionID,
                                   const std::string& timestamp,
                                   const std::string& status,
                                   const std::string& captureMethod)
    : studentID(studentID), sessionID(sessionID), timestamp(timestamp),
      status(status), captureMethod(captureMethod) {}

std::string AttendanceRecord::getStudentID() const { return studentID; }
std::string AttendanceRecord::getSessionID() const { return sessionID; }
std::string AttendanceRecord::getTimestamp() const { return timestamp; }
std::string AttendanceRecord::getStatus() const { return status; }
std::string AttendanceRecord::getCaptureMethod() const { return captureMethod; }

bool AttendanceRecord::isImmutable() const {
    return true;
}
