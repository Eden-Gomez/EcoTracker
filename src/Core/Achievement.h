#ifndef ACHIEVEMENTSYSTEM_H
#define ACHIEVEMENTSYSTEM_H

#include <map>
#include <string>

class ActionLogger; // Forward declaration

class AchievementSystem {
private:
    std::map<std::string, bool> achievements = {
            {"First Step", false},
            {"Carbon Saver", false},
            {"Vegan Week", false},
            {"Bike Master", false},
            {"Eco Hero", false}
    };

public:
    void checkAchievements(const ActionLogger& logger);
    void displayAchievements() const;
    bool isUnlocked(const std::string& achievement) const;
};

#endif // ACHIEVEMENTSYSTEM_H