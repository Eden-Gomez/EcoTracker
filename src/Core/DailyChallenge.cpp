#include "DailyChallenge.h"
#include <ctime>
#include <sstream>

DailyChallenge::DailyChallenge(std::string desc, int target)
        : description(std::move(desc)), targetValue(target),
          startDate(std::time(nullptr)) {}

void DailyChallenge::updateProgress(int amount) {
    currentValue += amount;
}

bool DailyChallenge::isCompleted() const {
    return currentValue >= targetValue;
}

bool DailyChallenge::isExpired() const {
    const int SECONDS_PER_DAY = 86400;
    return (std::time(nullptr) - startDate) > SECONDS_PER_DAY;
}

std::string DailyChallenge::getStatus() const {
    std::ostringstream status;
    status << "Challenge: " << description
           << "\nProgress: " << currentValue << "/" << targetValue
           << "\nStatus: " << (isCompleted() ? "✅ Completed" : "🕒 In Progress")
           << "\nTime Left: " << (24 - (std::time(nullptr) - startDate)/3600) << " hours";
    return status.str();
}