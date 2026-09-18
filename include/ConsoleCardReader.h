#ifndef CONSOLE_CARD_READER_H
#define CONSOLE_CARD_READER_H

#include "AttendanceCapture.h"

class ConsoleCardReader : public AttendanceCapture {
public:
    void beginSession() override;
    std::string captureNext() override;
    void endSession() override;
    std::string getCaptureMethod() const override { return "ConsoleCardReader"; }
};

#endif
