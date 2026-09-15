#ifndef CONSOLE_CARD_READER_H
#define CONSOLE_CARD_READER_H

#include "AttendanceCapture.h"

// ==========================================
// Concrete strategy: simulates a physical card-swipe reader
// by prompting for student IDs on the console, one at a time.
// ==========================================
class ConsoleCardReader : public AttendanceCapture {
public:
    void beginSession() override;
    std::string captureNext() override;
    void endSession() override;
};

#endif // CONSOLE_CARD_READER_H
