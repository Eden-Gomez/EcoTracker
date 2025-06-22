//#include "UserProfile.h"
//#include <fstream>
//#include <iostream>
//
//UserProfile::UserProfile(const std::string& name) : username(name) {}
//
//void UserProfile::addPoints(int points) {
//    carbonPoints += points;
//}
//
//void UserProfile::displayProfile() const {
//    std::cout << "User: " << username
//              << "\nCarbon Hero Points: " << carbonPoints << "\n";
//}
//void UserProfile::saveToFile(const std::string& filename) const {
//    std::ofstream file(filename);
//    if (file) {
//        file << username << "\n" << carbonPoints;
//    } else {
//        throw std::runtime_error("Cannot save file!");
//    }
//}
//
//void UserProfile::loadFromFile(const std::string& filename) {
//    std::ifstream file(filename);
//    if (file) {
//        file >> username >> carbonPoints;
//    } else {
//        throw std::runtime_error("Cannot load file!");
//    }
//}

#include "UserProfile.h"
#include <fstream>
#include <iostream>
#include <filesystem> // for std::filesystem

UserProfile::UserProfile(const std::string& name) : username(name), carbonPoints(0) {}

void UserProfile::addPoints(int points) {
    carbonPoints += points;
}

void UserProfile::displayProfile() const {
    std::cout << "User: " << username
              << "\nCarbon Hero Points: " << carbonPoints << "\n";
}

void UserProfile::saveToFile(const std::string& filename) const {
    // Ensure the directory exists (if specified)
    std::filesystem::path path(filename);
    std::filesystem::path parent = path.parent_path();
    if (!parent.empty()) {
        std::filesystem::create_directories(parent);
    }

    std::ofstream file(filename);
    if (file) {
        file << username << '\n';
        file << carbonPoints << '\n';

        // TODO: Save other future fields here
        // file << veganStreak << '\n';
        // file << level << '\n';
    } else {
        throw std::runtime_error("❌ Cannot save file: " + filename);
    }
}

void UserProfile::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file) {
        std::getline(file, username);  // safer than >> to allow spaces
        file >> carbonPoints;

        // TODO: Load other future fields here
        // file >> veganStreak;
        // file >> level;

    } else {
        throw std::runtime_error("❌ Cannot load file: " + filename);
    }
}
