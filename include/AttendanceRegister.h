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

    // Prevent copying due to owned raw pointers
    AttendanceRegister(const AttendanceRegister&) = delete;
    AttendanceRegister& operator=(const AttendanceRegister&) = delete;

    void openSession(const TimetableSlot& slot);
    void addRecord(const AttendanceRecord& record);
    void appendCorrection(const CorrectionRecord& record);
    float calculatePercentage(const std::string& studentID) const;
};

#endif // ATTENDANCE_REGISTER_H
