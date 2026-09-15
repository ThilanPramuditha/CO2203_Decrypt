#include "../include/AttendanceSession.h"
#include "../include/AttendanceCapture.h"
#include <iostream>
#include <stdexcept>

int AttendanceSession::defaultExpiryDuration = 15;

AttendanceSession::AttendanceSession(const std::string& sessionID, const std::string& sessionDate)
    : sessionID(sessionID), sessionDate(sessionDate), activeMechanism(nullptr) {}

void AttendanceSession::setCaptureMechanism(AttendanceCapture* mechanism) {
    activeMechanism = mechanism;
}

void AttendanceSession::executeCapture() {
    if (activeMechanism == nullptr) {
        throw std::runtime_error("No capture mechanism set for session " + sessionID);
    }

    activeMechanism->beginSession();

    while (true) {
        std::string id = activeMechanism->captureNext();
        if (id == "exit" || id.empty()) {
            break;
        }
        std::cout << "Captured attendance for: " << id << "\n";
    }

    activeMechanism->endSession();
}

std::string AttendanceSession::getSessionID() const { return sessionID; }
std::string AttendanceSession::getSessionDate() const { return sessionDate; }

int AttendanceSession::getDefaultExpiryDuration() { return defaultExpiryDuration; }
void AttendanceSession::setDefaultExpiryDuration(int minutes) { defaultExpiryDuration = minutes; }
