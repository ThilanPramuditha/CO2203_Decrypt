#ifndef ATTENDANCE_SESSION_H
#define ATTENDANCE_SESSION_H

#include <string>

class AttendanceCapture;

class AttendanceSession {
private:
    std::string sessionID;
    std::string sessionDate;
    static int defaultExpiryDuration;
    AttendanceCapture* activeMechanism;

public:
    AttendanceSession(const std::string& sessionID, const std::string& sessionDate);

    void setCaptureMechanism(AttendanceCapture* mechanism);
    void executeCapture();

    std::string getSessionID() const;
    std::string getSessionDate() const;

    static int getDefaultExpiryDuration();
    static void setDefaultExpiryDuration(int minutes);
};

#endif // ATTENDANCE_SESSION_H
