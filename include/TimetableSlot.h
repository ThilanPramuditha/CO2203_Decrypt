#ifndef TIMETABLE_SLOT_H
#define TIMETABLE_SLOT_H

#include <string>
#include <iosfwd>   // forward-declares std::ostream without pulling in <iostream>

// ==========================================
// Represents one scheduled block of time.
// Used both by Course (its fixed schedule) and by
// Timetable (a Student's collection of slots).
// ==========================================
class TimetableSlot {
private:
    int dayOfWeek;     // e.g. 0 = Monday ... 6 = Sunday
    int startTime;     // 24hr format, e.g. 1400 for 2:00 PM
    int endTime;
    std::string location;

public:
    TimetableSlot(int day, int start, int end, const std::string& loc);

    // Getters
    int getDayOfWeek() const;
    int getStartTime() const;
    int getEndTime() const;
    std::string getLocation() const;

    // Two slots are "equal" (for clash purposes) if they overlap
    // in day and time range.
    bool operator==(const TimetableSlot& other) const;

    friend std::ostream& operator<<(std::ostream& os, const TimetableSlot& slot);
};

#endif // TIMETABLE_SLOT_H
