#include "../include/AttendanceSession.h"
#include "../include/CustomException.h"
#include <iostream>

// Static member definition (must live in exactly one .cpp file).
// Sessions stay open for 15 minutes by default unless changed.
int AttendanceSession::defaultExpiryDuration = 15;

AttendanceSession::AttendanceSession(const std::string& sessionID, const std::string& sessionDate)
    : sessionID(sessionID), sessionDate(sessionDate), activeMechanism(nullptr) {}

// Aggregation: just points at the mechanism, does not take ownership
// (see the destructor's absence of a `delete activeMechanism;`).
void AttendanceSession::setCaptureMechanism(AttendanceCapture* mechanism) {
    activeMechanism = mechanism;
}

// Drives the Strategy: the session has no idea whether activeMechanism
// is a ConsoleCardReader or a QRCodeCapture -- it just calls the
// interface and polymorphism routes it to the right implementation.
void AttendanceSession::executeCapture() {
    if (activeMechanism == nullptr) {
        throw CustomException("No capture mechanism set for session " + sessionID);
    }

    activeMechanism->beginSession();

    while (true) {
        std::string id = activeMechanism->captureNext();
        if (id == "exit" || id.empty()) {
            break;
        }
        // NOTE: this session only captures raw student IDs. Turning each
        // captured ID into an AttendanceRecord (with timestamp, status,
        // capture method) and appending it via AttendanceRegister::addRecord()
        // is the orchestrator's job (e.g. Lecturer), since it has access to
        // both this session and the owning AttendanceRegister.
        std::cout << "Captured attendance for: " << id << "\n";
    }

    activeMechanism->endSession();
}

std::string AttendanceSession::getSessionID() const { return sessionID; }
std::string AttendanceSession::getSessionDate() const { return sessionDate; }

int AttendanceSession::getDefaultExpiryDuration() { return defaultExpiryDuration; }
void AttendanceSession::setDefaultExpiryDuration(int minutes) { defaultExpiryDuration = minutes; }
