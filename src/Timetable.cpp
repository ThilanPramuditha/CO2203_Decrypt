#include "Timetable.h"
#include "CustomExceptions.h"
#include <ostream>

void Timetable::addSlot(const TimetableSlot& slot) {
    if (checkClash(slot)) {
        throw ClashException("New slot clashes with an existing timetable entry.");
    }
    slots.push_back(slot);
}

void Timetable::removeSlot(const TimetableSlot& slot) {
    for (auto it = slots.begin(); it != slots.end(); ++it) {
        if (*it == slot) {
            slots.erase(it);
            break;
        }
    }
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
