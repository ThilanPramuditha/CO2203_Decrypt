#include "AttendanceRegister.h"
#include "TimetableSlot.h"
#include "CustomExceptions.h"
#include <ctime>
#include <sstream>

AttendanceRegister::~AttendanceRegister() {
    for (AttendanceSession* session : sessions) {
        delete session;
    }
    sessions.clear();
}

void AttendanceRegister::openSession(const TimetableSlot& slot) {
    std::ostringstream idStream;
    idStream << "SESSION-" << (sessions.size() + 1);

    std::time_t now = std::time(nullptr);
    char dateBuffer[11];
    std::strftime(dateBuffer, sizeof(dateBuffer), "%Y-%m-%d", std::localtime(&now));

    std::string sessionDateInfo = std::string(dateBuffer) + " (Day " + std::to_string(slot.getDayOfWeek()) + " @" + slot.getLocation() + ")";

    AttendanceSession* newSession = new AttendanceSession(idStream.str(), sessionDateInfo);
    sessions.push_back(newSession);
}

void AttendanceRegister::addRecord(const AttendanceRecord& record) {
    for (const auto& existing : records) {
        if (existing.getStudentID() == record.getStudentID() &&
            existing.getSessionID() == record.getSessionID()) {
            throw DuplicateAttendanceException("Student " + record.getStudentID() + " already marked present in session " + record.getSessionID());
        }
    }
    records.push_back(record);
}

void AttendanceRegister::appendCorrection(const CorrectionRecord& record) {
    corrections.push_back(record);
}

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
