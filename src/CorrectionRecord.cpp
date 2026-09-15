#include "../include/CorrectionRecord.h"

CorrectionRecord::CorrectionRecord(const std::string& lecturer, const std::string& reason)
    : actingLecturer(lecturer), reason(reason) {}

std::string CorrectionRecord::getActingLecturer() const { return actingLecturer; }
std::string CorrectionRecord::getReason() const { return reason; }
