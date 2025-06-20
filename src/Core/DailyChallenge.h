#ifndef DAILYCHALLENGE_H
#define DAILYCHALLENGE_H

#include <string>
#include <ctime>

class DailyChallenge {
private:
    std::string description;
    int targetValue;
    int currentValue = 0;
    std::time_t startDate;

public:
    DailyChallenge(std::string desc, int target);
    void updateProgress(int amount);
    bool isCompleted() const;
    std::string getStatus() const;
    bool isExpired() const;
};

#endif