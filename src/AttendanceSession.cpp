#include "AttendanceSession.h"
#include "AttendanceCapture.h"
#include "CustomExceptions.h"
#include <iostream>

int AttendanceSession::defaultExpiryDuration = 15;

AttendanceSession::AttendanceSession(const std::string& sessionID, const std::string& sessionDate)
    : sessionID(sessionID), sessionDate(sessionDate), activeMechanism(nullptr) {}

void AttendanceSession::setCaptureMechanism(AttendanceCapture* mechanism) {
    activeMechanism = mechanism;
}

#include "AttendanceRegister.h"
#include <ctime>

void AttendanceSession::executeCapture(AttendanceRegister* reg) {
    if (activeMechanism == nullptr) {
        throw CustomException("No capture mechanism set for session " + sessionID);
    }

    activeMechanism->beginSession();

    while (true) {
        std::string id = activeMechanism->captureNext();
        if (id == "exit" || id.empty()) {
            break;
        }
        
        std::time_t now = std::time(nullptr);
        char ts[20];
        std::strftime(ts, sizeof(ts), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        
        AttendanceRecord record(id, sessionID, ts, "PRESENT", "ConsoleCardReader");
        
        try {
            reg->addRecord(record);
            std::cout << "Captured attendance for: " << id << "\n";
        } catch (const CustomException& e) {
            std::cout << "[Error] " << e.what() << "\n";
        }
    }

    activeMechanism->endSession();
}

std::string AttendanceSession::getSessionID() const { return sessionID; }
std::string AttendanceSession::getSessionDate() const { return sessionDate; }

int AttendanceSession::getDefaultExpiryDuration() { return defaultExpiryDuration; }
void AttendanceSession::setDefaultExpiryDuration(int minutes) { defaultExpiryDuration = minutes; }
