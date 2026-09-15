#include "../include/Timetable.h"
#include <ostream>
#include <stdexcept>

void Timetable::addSlot(const TimetableSlot& slot) {
    if (checkClash(slot)) {
        throw std::runtime_error("New slot clashes with an existing timetable entry.");
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
