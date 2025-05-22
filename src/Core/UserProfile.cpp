#include "UserProfile.h"
#include <fstream>
#include <iostream>

UserProfile::UserProfile(const std::string& name) : username(name) {}

void UserProfile::addPoints(int points) {
    carbonPoints += points;
}

void UserProfile::displayProfile() const {
    std::cout << "User: " << username
              << "\nCarbon Hero Points: " << carbonPoints << "\n";
}
void UserProfile::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (file) {
        file << username << "\n" << carbonPoints;
    } else {
        throw std::runtime_error("Cannot save file!");
    }
}

void UserProfile::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file) {
        file >> username >> carbonPoints;
    } else {
        throw std::runtime_error("Cannot load file!");
    }
}
int UserProfile::getCarbonPoints() const {
    return carbonPoints;
}
