#include "../include/Timetable.h"
#include "../include/CustomException.h"
#include <ostream>

// Guards against overlapping slots: refuses to add a slot that
// clashes with something already on the timetable.
void Timetable::addSlot(const TimetableSlot& slot) {
    if (checkClash(slot)) {
        throw ClashException("New slot clashes with an existing timetable entry.");
    }
    slots.push_back(slot);
}

// Uses the overloaded == on TimetableSlot (day + time-interval overlap)
// to detect whether the given slot would clash with any existing one.
bool Timetable::checkClash(const TimetableSlot& slot) const {
    for (const auto& existingSlot : slots) {
        if (existingSlot == slot) {
            return true;
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Timetable& t) {
    for (const auto& slot : t.slots) {
        os << slot << "\n";
    }
    return os;
}
