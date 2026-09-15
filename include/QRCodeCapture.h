#ifndef QR_CODE_CAPTURE_H
#define QR_CODE_CAPTURE_H

#include "AttendanceCapture.h"

// ==========================================
// Concrete strategy: generates a one-time session token that
// students "scan" (in this simulation, submit) to check in.
// ==========================================
class QRCodeCapture : public AttendanceCapture {
private:
    std::string sessionToken;

public:
    void beginSession() override;
    std::string captureNext() override;
    void endSession() override;
};

#endif // QR_CODE_CAPTURE_H
