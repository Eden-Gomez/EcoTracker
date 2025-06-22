#include "GUI/Menu.h"
#include "Core/UserProfile.h"
#include "GUI/Dashboard.h"
#include "Core/TransportAction.h"
#include "Core/ActionLogger.h"
#include "Core/FoodChoice.h"
#include "Core/Achievement.h"
#include <iostream>
#include <filesystem>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

// Helper: List saved profiles
std::vector<std::string> listSavedProfiles(const std::string& directory) {
    std::vector<std::string> files;
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();

            // Manually check: ends with ".txt" and does NOT start with "actions_"
            bool endsWithTxt = filename.size() >= 4 && filename.substr(filename.size() - 4) == ".txt";
            bool startsWithActions = filename.size() >= 8 && filename.substr(0, 8) == "actions_";

            if (endsWithTxt && !startsWithActions) {
                files.push_back(filename);
            }
        }
    }
    return files;
}



// Choose from list
std::string chooseFileFromList(const std::vector<std::string>& files, const std::string& prompt) {
    if (files.empty()) {
        std::cout << "⚠️ No saved profiles found.\n";
        return "";
    }

    std::cout << "\n📂 " << prompt << "\n";
    for (size_t i = 0; i < files.size(); ++i) {
        std::cout << i + 1 << ") " << files[i] << '\n';
    }

    int choice;
    while (true) {
        std::cout << "Enter number to select: ";
        if (std::cin >> choice && choice >= 1 && choice <= static_cast<int>(files.size())) {
            break;
        }
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid selection, try again.\n";
    }

    return files[choice - 1];
}

float getValidatedInput(const std::string& prompt) {
    while (true) {
        std::string inputStr;
        std::cout << prompt << " (or ? for help): ";
        std::cin >> inputStr;

        if (inputStr == "?") {
            std::cout << "\n🔍 CO₂ reference not yet implemented.\n";
            continue;
        }

        try {
            return std::stof(inputStr);
        } catch (...) {
            std::cout << "❌ Invalid number! Try again.\n";
        }
    }
}

void logNewAction(UserProfile& user, ActionLogger& logger, AchievementSystem& achievements, DailyChallenge& challenge) {
    Menu typeMenu("Select Action Type");
    typeMenu.addItem("Transportation");
    typeMenu.addItem("Food Choice");
    typeMenu.addItem("Go Back to Main Menu");

    switch (typeMenu.display()) {
        case 1: {
            std::string vehicle;
            float co2 = getValidatedInput("CO₂ saved (kg)");
            std::cin.ignore();
            std::cout << "Vehicle type: ";
            std::getline(std::cin, vehicle);
            auto transport = std::make_unique<TransportAction>(vehicle, co2);
            int points = transport->calculatePoints();
            user.addPoints(points);
            transport->applyEffects(user, challenge);
            logger.addAction(std::move(transport));
            break;
        }
        case 2: {
            std::string meal;
            float co2 = getValidatedInput("CO₂ saved (kg)");
            std::cin.ignore();
            std::cout << "Meal description: ";
            std::getline(std::cin, meal);

            bool vegan = false;
            int v;
            while (true) {
                std::cout << "Vegan? (1=Yes, 0=No): ";
                if (std::cin >> v && (v == 0 || v == 1)) {
                    vegan = v;
                    break;
                }
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input.\n";
            }

            auto food = std::make_unique<FoodChoice>(meal, vegan, co2);
            int points = food->calculatePoints();
            user.addPoints(points);
            logger.addAction(std::move(food));
            break;
        }
        case 3:
            return;
    }

    achievements.checkAchievements(logger);
    std::cout << "\n✅ Action logged. Achievement progress updated.\n";
    std::cin.ignore();
}

void mainMenuLoop(UserProfile& user, Dashboard& dashboard, ActionLogger& logger, AchievementSystem& achievements, const std::string& originalProfileFile) {
    Menu mainMenu("Main Menu");
    mainMenu.addItem("View Dashboard");
    mainMenu.addItem("Log New Action");
    mainMenu.addItem("Save Progress");
    mainMenu.addItem("Load Profile");
    mainMenu.addItem("Exit Game");

    DailyChallenge challenge("Save 10kg CO₂ today!", 10);

    while (true) {
        switch (mainMenu.display()) {
            case 1:
                dashboard.display();
                std::cout << "Press Enter to continue...";
                std::cin.ignore();
                std::cin.get();
                break;

            case 2:
                logNewAction(user, logger, achievements, challenge);
                break;

            case 3: {
                std::vector<std::string> files = listSavedProfiles("data");
                files.push_back("🆕 Save As New");

                std::string selectedFile = chooseFileFromList(files, "Choose a file to save progress into:");
                if (selectedFile == "🆕 Save As New") {
                    std::cin.ignore();
                    std::string newName;
                    std::cout << "Enter new save name (no extension): ";
                    std::getline(std::cin, newName);

                    user.saveToFile("data/" + newName + ".txt");
                    logger.saveToFile("data/actions_" + newName + ".txt");
                } else if (!selectedFile.empty()) {
                    std::string nameOnly = selectedFile.substr(0, selectedFile.find(".txt"));
                    user.saveToFile("data/" + nameOnly + ".txt");
                    logger.saveToFile("data/actions_" + nameOnly + ".txt");
                }
                break;
            }

            case 4: {
                std::vector<std::string> files = listSavedProfiles("data");
                std::string selectedFile = chooseFileFromList(files, "Choose a profile to load:");
                if (!selectedFile.empty()) {
                    std::string nameOnly = selectedFile.substr(0, selectedFile.find(".txt"));
                    user.loadFromFile("data/" + nameOnly + ".txt");
                    logger.loadFromFile("data/actions_" + nameOnly + ".txt");
                    std::cout << "✅ Loaded profile: " << nameOnly << "\n";
                }
                break;
            }

            case 5:
                std::cout << "👋 Exiting game.\n";
                return;
        }
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::filesystem::create_directories("data");

    Menu startMenu("Welcome to EcoTracker!");
    startMenu.addItem("Start New Game");
    startMenu.addItem("Load Previously Saved Game");

    std::string profileName;
    std::string profileFile;
    std::string actionsFile;
    ActionLogger logger;
    AchievementSystem achievements;

    switch (startMenu.display()) {
        case 1: {
            std::cin.ignore();
            std::cout << "Enter your profile name: ";
            std::getline(std::cin, profileName);
            profileFile = "data/" + profileName + ".txt";
            actionsFile = "data/actions_" + profileName + ".txt";
            break;
        }
        case 2: {
            std::vector<std::string> files = listSavedProfiles("data");
            std::string selectedFile = chooseFileFromList(files, "Choose a profile to load:");
            if (selectedFile.empty()) return 0;
            profileName = selectedFile.substr(0, selectedFile.find(".txt"));
            profileFile = "data/" + profileName + ".txt";
            actionsFile = "data/actions_" + profileName + ".txt";
            break;
        }
    }

    UserProfile user(profileName);

    try {
        user.loadFromFile(profileFile);
    } catch (...) {
        std::cout << "🆕 Starting fresh for user: " << profileName << "\n";
    }

    try {
        logger.loadFromFile(actionsFile);
    } catch (...) {
        std::cout << "🗒️ No previous actions found.\n";
    }

    Dashboard dashboard(user, logger);
    mainMenuLoop(user, dashboard, logger, achievements, profileFile);
    return 0;
}
