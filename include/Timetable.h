#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <vector>
#include <iosfwd>
#include "TimetableSlot.h"

class Timetable {
private:
    std::vector<TimetableSlot> slots;

public:
    Timetable() = default;

    void addSlot(const TimetableSlot& slot);
    bool checkClash(const TimetableSlot& slot) const;

    friend std::ostream& operator<<(std::ostream& os, const Timetable& t);
};

#endif // TIMETABLE_H
