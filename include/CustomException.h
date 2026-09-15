#ifndef CUSTOM_EXCEPTION_H
#define CUSTOM_EXCEPTION_H

#include <exception>
#include <string>

// ==========================================
// Base exception for the whole system.
// Every custom exception type derives from this
// so callers can catch (CustomException&) generically,
// or catch the specific subtype if they need to.
// ==========================================
class CustomException : public std::exception {
protected:
    std::string errorMessage;

public:
    explicit CustomException(const std::string& msg) : errorMessage(msg) {}

    // override of std::exception::what()
    const char* what() const noexcept override {
        return errorMessage.c_str();
    }

    virtual ~CustomException() = default;
};

// Thrown when a lecturer/system tries to record attendance
// for a student who has already been marked in the same session.
class DuplicateAttendanceException : public CustomException {
public:
    explicit DuplicateAttendanceException(const std::string& msg)
        : CustomException(msg) {}
};

// Thrown when a capture mechanism or register operation is
// attempted on a session that has already been closed.
class SessionClosedException : public CustomException {
public:
    explicit SessionClosedException(const std::string& msg)
        : CustomException(msg) {}
};

// Thrown when a course/session has reached its capacity limit.
class CapacityException : public CustomException {
public:
    explicit CapacityException(const std::string& msg)
        : CustomException(msg) {}
};

// Thrown when adding a TimetableSlot would clash with
// an existing slot in a Timetable.
class ClashException : public CustomException {
public:
    explicit ClashException(const std::string& msg)
        : CustomException(msg) {}
};

#endif // CUSTOM_EXCEPTION_H
