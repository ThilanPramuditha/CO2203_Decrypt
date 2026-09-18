#ifndef QR_CODE_CAPTURE_H
#define QR_CODE_CAPTURE_H

#include "AttendanceCapture.h"
#include <ctime>

class QRCodeCapture : public AttendanceCapture {
private:
    std::string sessionToken;
    std::time_t sessionStartTime;

public:
    void beginSession() override;
    std::string captureNext() override;
    void endSession() override;
    std::string getCaptureMethod() const override { return "QRCodeCapture"; }
};

#endif
