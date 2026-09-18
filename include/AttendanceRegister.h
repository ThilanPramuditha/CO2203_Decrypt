#ifndef ATTENDANCE_REGISTER_H
#define ATTENDANCE_REGISTER_H

#include <vector>
#include <string>
#include "AttendanceSession.h"
#include "AttendanceRecord.h"
#include "CorrectionRecord.h"

class TimetableSlot;

class AttendanceRegister {
private:
    std::vector<AttendanceSession*> sessions;
    std::vector<AttendanceRecord> records;
    std::vector<CorrectionRecord> corrections;

public:
    AttendanceRegister() = default;
    ~AttendanceRegister();

    AttendanceRegister(const AttendanceRegister&) = delete;
    AttendanceRegister& operator=(const AttendanceRegister&) = delete;

    void openSession(const TimetableSlot& slot);
    void restoreSession(const std::string& sessionID);
    AttendanceSession* getActiveSession() const;
    void addRecord(const AttendanceRecord& record);
    void appendCorrection(const CorrectionRecord& record);
    float calculatePercentage(const std::string& studentID) const;
    const std::vector<AttendanceRecord>& getRecords() const { return records; }
};

#endif
