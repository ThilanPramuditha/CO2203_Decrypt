#ifndef TIMETABLE_SLOT_H
#define TIMETABLE_SLOT_H

#include <string>
#include <iosfwd>

class TimetableSlot {
private:
    int dayOfWeek;
    int startTime;
    int endTime;
    std::string location;

public:
    TimetableSlot(int day, int start, int end, const std::string& loc);

    int getDayOfWeek() const;
    int getStartTime() const;
    int getEndTime() const;
    std::string getLocation() const;

    bool operator==(const TimetableSlot& other) const;

    friend std::ostream& operator<<(std::ostream& os, const TimetableSlot& slot);
};

#endif
