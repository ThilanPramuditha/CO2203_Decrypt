#ifndef CORRECTION_RECORD_H
#define CORRECTION_RECORD_H

#include <string>

class CorrectionRecord {
private:
    std::string actingLecturer;
    std::string reason;

public:
    CorrectionRecord(const std::string& lecturer, const std::string& reason);

    std::string getActingLecturer() const;
    std::string getReason() const;
};

#endif
