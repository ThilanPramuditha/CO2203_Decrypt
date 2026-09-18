#include "AttendanceSession.h"
#include "AttendanceCapture.h"
#include "CustomExceptions.h"
#include <iostream>
#include <cctype>

int AttendanceSession::defaultExpiryDuration = 15;

AttendanceSession::AttendanceSession(const std::string& sessionID, const std::string& sessionDate)
    : sessionID(sessionID), sessionDate(sessionDate), activeMechanism(nullptr) {}

void AttendanceSession::setCaptureMechanism(AttendanceCapture* mechanism) {
    activeMechanism = mechanism;
}

#include "AttendanceRegister.h"
#include "Course.h"
#include <ctime>

void AttendanceSession::executeCapture(Course* course) {
    if (activeMechanism == nullptr) {
        throw CustomException("No capture mechanism set for session " + sessionID);
    }

    AttendanceRegister* reg = course->getRegister();
    activeMechanism->beginSession();

    while (true) {
        std::string id = activeMechanism->captureNext();
        
        std::string lowerId = id;
        for (char& c : lowerId) c = std::tolower(c);
        
        if (lowerId == "exit" || id.empty()) {
            break;
        }
        
        try {
            if (!course->isStudentEnrolled(id)) {
                throw NotEnrolledException("Student " + id + " is not enrolled in this course.");
            }
            
            std::time_t now = std::time(nullptr);
            char ts[20];
            std::strftime(ts, sizeof(ts), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
            
            AttendanceRecord record(id, sessionID, ts, "PRESENT", activeMechanism->getCaptureMethod());
            
            reg->addRecord(record);
            std::cout << "Captured attendance for: " << id << "\n";
        } catch (const CustomException& e) {
            std::cout << "[ERROR] " << e.what() << "\n";
        }
    }

    activeMechanism->endSession();
}

std::string AttendanceSession::getSessionID() const { return sessionID; }
std::string AttendanceSession::getSessionDate() const { return sessionDate; }

int AttendanceSession::getDefaultExpiryDuration() { return defaultExpiryDuration; }
void AttendanceSession::setDefaultExpiryDuration(int minutes) { defaultExpiryDuration = minutes; }
