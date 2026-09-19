#ifndef ATTENDANCE_SESSION_H
#define ATTENDANCE_SESSION_H

#include <string>
#include <ctime>

class AttendanceCapture;

class AttendanceSession {
private:
    std::string sessionID;
    std::string sessionDate;
    static int defaultExpiryDuration;
    AttendanceCapture* activeMechanism;
    bool isOpen;
    std::time_t openTime;

public:
    AttendanceSession(const std::string& sessionID, const std::string& sessionDate);

    void setCaptureMechanism(AttendanceCapture* mechanism);
    void executeCapture(class Course* course);

    std::string getSessionID() const;
    std::string getSessionDate() const;

    void close();

    static int getDefaultExpiryDuration();
    static void setDefaultExpiryDuration(int minutes);
};

#endif
