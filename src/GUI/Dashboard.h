#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "../Core/UserProfile.h"
#include <vector>
#include <string>

class Dashboard {
private:
    const UserProfile& user;
    std::vector<std::string> recentActions;

    void printHeader() const;
    void printProgressBar(float percentage) const;

public:
    explicit Dashboard(const UserProfile& profile);
    void addAction(const std::string& action);
    void display() const;
};

#endif // DASHBOARD_H