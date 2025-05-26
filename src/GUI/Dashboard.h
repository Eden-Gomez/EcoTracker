#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "../Core/UserProfile.h"
#include "../Core/ActionLogger.h"
#include "../Core/Achievement.h"
#include <vector>

class Dashboard {
private:
    const UserProfile& user;
    const ActionLogger& logger;
    mutable AchievementSystem achievements;  // ADD

    void printHeader() const;
    void printProgressBar(float percentage) const;

public:
    Dashboard(const UserProfile& profile, const ActionLogger& actionLogger);
    void display() const;
};

#endif