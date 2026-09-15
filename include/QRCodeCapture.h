#ifndef QR_CODE_CAPTURE_H
#define QR_CODE_CAPTURE_H

#include "AttendanceCapture.h"

class QRCodeCapture : public AttendanceCapture {
private:
    std::string sessionToken;

public:
    void beginSession() override;
    std::string captureNext() override;
    void endSession() override;
};

#endif // QR_CODE_CAPTURE_H
