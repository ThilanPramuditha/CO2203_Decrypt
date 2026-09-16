#include "Timetable.h"
#include "CustomExceptions.h"
#include <ostream>

void Timetable::addSlot(const TimetableSlot& slot) {
    if (checkClash(slot)) {
        throw ClashException("New slot clashes with an existing timetable entry.");
    }
    slots.push_back(slot);
}

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
