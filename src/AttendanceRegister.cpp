#include "../include/AttendanceRegister.h"
#include "../include/CustomException.h"
#include "../include/TimetableSlot.h"
#include <ctime>
#include <sstream>

// Composition: AttendanceRegister owns its AttendanceSession objects,
// so it deletes every one of them when the register itself is destroyed.
AttendanceRegister::~AttendanceRegister() {
    for (AttendanceSession* session : sessions) {
        delete session;
    }
    sessions.clear();
}

// Creates a new AttendanceSession tied to the given scheduled slot
// and adds it to this register's history.
void AttendanceRegister::openSession(const TimetableSlot& slot) {
    // Simple ID scheme: SESSION-<count>. Real systems might hash the
    // slot + timestamp, but this keeps Day 1's header contract intact.
    std::ostringstream idStream;
    idStream << "SESSION-" << (sessions.size() + 1);

    std::time_t now = std::time(nullptr);
    char dateBuffer[11];
    std::strftime(dateBuffer, sizeof(dateBuffer), "%Y-%m-%d", std::localtime(&now));

    AttendanceSession* newSession = new AttendanceSession(idStream.str(), dateBuffer);
    sessions.push_back(newSession);
    // Note: slot is accepted per the header contract but this register
    // doesn't need to store it directly -- Course already owns the
    // TimetableSlot that this session corresponds to.
    (void)slot;
}

// Rejects a record if this exact student already has one for this
// exact session (prevents double-marking the same student twice).
void AttendanceRegister::addRecord(const AttendanceRecord& record) {
    for (const auto& existing : records) {
        if (existing.getStudentID() == record.getStudentID() &&
            existing.getSessionID() == record.getSessionID()) {
            throw DuplicateAttendanceException(
                "Student " + record.getStudentID() +
                " already has an attendance record for session " + record.getSessionID());
        }
    }
    records.push_back(record);
}

void AttendanceRegister::appendCorrection(const CorrectionRecord& record) {
    corrections.push_back(record);
}

// Percentage of this register's sessions where the given student
// has a PRESENT record.
float AttendanceRegister::calculatePercentage(const std::string& studentID) const {
    if (sessions.empty()) {
        return 0.0f;
    }

    int presentCount = 0;
    for (const auto& record : records) {
        if (record.getStudentID() == studentID && record.getStatus() == "PRESENT") {
            presentCount++;
        }
    }

    return (static_cast<float>(presentCount) / static_cast<float>(sessions.size())) * 100.0f;
}
