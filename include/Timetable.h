#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <vector>
#include <iosfwd>
#include "TimetableSlot.h"

// ==========================================
// A Student's personal timetable: a composition of
// TimetableSlot objects (Timetable *-- "*" TimetableSlot).
// Responsible for detecting scheduling clashes before
// a new slot (e.g. from enrolling in a course) is added.
// ==========================================
class Timetable {
private:
    std::vector<TimetableSlot> slots;

public:
    Timetable() = default;

    // Adds a slot to the timetable. Implementations should call
    // checkClash() first and throw ClashException if it overlaps.
    void addSlot(const TimetableSlot& slot);

    // Returns true if the given slot overlaps with any existing slot.
    bool checkClash(const TimetableSlot& slot) const;

    friend std::ostream& operator<<(std::ostream& os, const Timetable& t);
};

#endif // TIMETABLE_H
