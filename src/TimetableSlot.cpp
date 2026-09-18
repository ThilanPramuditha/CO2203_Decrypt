#include "../include/TimetableSlot.h"
#include <ostream>
#include <iomanip>

TimetableSlot::TimetableSlot(int day, int start, int end, const std::string& loc)
    : dayOfWeek(day), startTime(start), endTime(end), location(loc) {}

int TimetableSlot::getDayOfWeek() const { return dayOfWeek; }
int TimetableSlot::getStartTime() const { return startTime; }
int TimetableSlot::getEndTime() const { return endTime; }
std::string TimetableSlot::getLocation() const { return location; }

bool TimetableSlot::operator==(const TimetableSlot& other) const {
    bool sameDay = (dayOfWeek == other.dayOfWeek);
    bool timesOverlap = (startTime < other.endTime) && (other.startTime < endTime);
    return sameDay && timesOverlap;
}

std::ostream& operator<<(std::ostream& os, const TimetableSlot& slot) {
    static const char* dayNames[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    std::string dayLabel = (slot.dayOfWeek >= 0 && slot.dayOfWeek <= 6)
                                ? dayNames[slot.dayOfWeek]
                                : "???";
    os << dayLabel << " " 
       << std::setfill('0') << std::setw(4) << slot.startTime << "-" 
       << std::setfill('0') << std::setw(4) << slot.endTime
       << " @ " << slot.location;
    return os;
}
