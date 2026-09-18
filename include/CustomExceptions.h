#ifndef CUSTOM_EXCEPTIONS_H
#define CUSTOM_EXCEPTIONS_H

#include <exception>
#include <string>

class CustomException : public std::exception {
private:
    std::string errorMessage;

public:
    explicit CustomException(std::string msg);
    virtual ~CustomException() = default;
    
    const char* what() const noexcept override;
};

class DuplicateAttendanceException : public CustomException {
public:
    explicit DuplicateAttendanceException(std::string msg);
};

class NotEnrolledException : public CustomException {
public:
    explicit NotEnrolledException(std::string msg);
};

class SessionClosedException : public CustomException {
public:
    explicit SessionClosedException(std::string msg);
};

class CapacityException : public CustomException {
public:
    explicit CapacityException(std::string msg);
};

class ClashException : public CustomException {
public:
    explicit ClashException(std::string msg);
};

#endif
