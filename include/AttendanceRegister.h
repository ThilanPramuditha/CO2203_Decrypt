#ifndef ATTENDANCE_REGISTER_H
#define ATTENDANCE_REGISTER_H

#include <vector>
#include <string>
#include "AttendanceSession.h"
#include "AttendanceRecord.h"
#include "CorrectionRecord.h"

class TimetableSlot; // forward declaration, avoids pulling in the full header

// ==========================================
// Belongs to exactly one Course (composition: Course *-- "1" AttendanceRegister).
// Owns the full attendance history for that course: every session ever
// opened, every record ever captured, and every manual correction made.
// ==========================================
class AttendanceRegister {
private:
    std::vector<AttendanceSession*> sessions;   // owned (composition)
    std::vector<AttendanceRecord> records;
    std::vector<CorrectionRecord> corrections;

public:
    AttendanceRegister() = default;
    ~AttendanceRegister(); // deletes owned AttendanceSession pointers

    // Opens a new AttendanceSession for the given scheduled slot.
    void openSession(const TimetableSlot& slot);

    // Appends a new record. Throws DuplicateAttendanceException if the
    // student already has a record for that sessionID.
    void addRecord(const AttendanceRecord& record);

    // Appends a manual correction (does not modify existing records).
    void appendCorrection(const CorrectionRecord& record);

    // Percentage of sessions the given student was marked PRESENT for.
    float calculatePercentage(const std::string& studentID) const;
};

#endif // ATTENDANCE_REGISTER_H
