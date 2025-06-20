#ifndef ACHIEVEMENTSYSTEM_H
#define ACHIEVEMENTSYSTEM_H


#include <string>
#include <vector>

class ActionLogger; // Forward declaration

struct Achievement {
    std::string name;
    bool unlocked;
    int current;
    int target;
};

class AchievementSystem {
private:
    std::vector<Achievement> achievements = {
            {"First Step",    false, 0, 1},
            {"Carbon Saver",  false, 0, 100},  // 100kg CO₂
            {"Vegan Week",    false, 0, 7},     // 7 consecutive days
            {"Bike Master",   false, 0, 10},    // 10 bike trips
            {"Eco Hero",      false, 0, 1000}   // 1000 total points
    };

public:
    void checkAchievements(const ActionLogger& logger);
    void displayAchievements() const;
    bool isUnlocked(const std::string& name) const;  // MODIFY: Parameter name
};


#endif