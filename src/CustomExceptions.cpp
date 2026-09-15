#include "CustomExceptions.h"

CustomException::CustomException(std::string msg) : errorMessage(std::move(msg)) {}

const char* CustomException::what() const noexcept {
    return errorMessage.c_str();
}

DuplicateAttendanceException::DuplicateAttendanceException(std::string msg) : CustomException(std::move(msg)) {}
NotEnrolledException::NotEnrolledException(std::string msg) : CustomException(std::move(msg)) {}
SessionClosedException::SessionClosedException(std::string msg) : CustomException(std::move(msg)) {}
CapacityException::CapacityException(std::string msg) : CustomException(std::move(msg)) {}
ClashException::ClashException(std::string msg) : CustomException(std::move(msg)) {}