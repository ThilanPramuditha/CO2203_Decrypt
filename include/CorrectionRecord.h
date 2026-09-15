#ifndef CORRECTION_RECORD_H
#define CORRECTION_RECORD_H

#include <string>

// ==========================================
// Since AttendanceRecord is immutable, any manual fix
// (e.g. a lecturer marking a student present who was
// missed by the capture device) is logged here instead,
// preserving a full audit trail.
// ==========================================
class CorrectionRecord {
private:
    std::string actingLecturer;
    std::string reason;

public:
    CorrectionRecord(const std::string& lecturer, const std::string& reason);

    std::string getActingLecturer() const;
    std::string getReason() const;
};

#endif // CORRECTION_RECORD_H
