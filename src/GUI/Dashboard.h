#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "../Core/UserProfile.h"
#include "../Core/ActionLogger.h"
#include <vector>
#include <string>

class Dashboard {
private:
    const UserProfile& user;
    const ActionLogger& logger;  // Add logger reference
    std::vector<std::string> recentActions;

    void printHeader() const;
    void printProgressBar(float percentage) const;

public:
//    explicit Dashboard(const UserProfile& profile);
    Dashboard(const UserProfile& profile, const ActionLogger& actionLogger);
    void addAction(const std::string& action);
    void display() const;
};

#endif // DASHBOARD_H