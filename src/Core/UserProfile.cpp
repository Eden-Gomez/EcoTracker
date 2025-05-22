#include "UserProfile.h"
#include <iostream>

UserProfile::UserProfile(const std::string& name) : username(name) {}

void UserProfile::addPoints(int points) {
    carbonPoints += points;
}

void UserProfile::displayProfile() const {
    std::cout << "User: " << username
              << "\nCarbon Hero Points: " << carbonPoints << "\n";
}