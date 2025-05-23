#include "GUI/Menu.h"
#include "Core/UserProfile.h"
#include "GUI/Dashboard.h"
#include "Core/TransportAction.h"
#include "Core/ActionLogger.h"
#include "Core/FoodChoice.h"
#include <iostream>
#include <windows.h>  // For SetConsoleOutputCP
#include <string>

// Show CO₂ help
void showCo2Reference() {
    std::cout << "\n🔍 Common CO₂ Savings Reference:\n"
              << "Transportation (per 10km):\n"
              << "  Car (Gasoline): 2.4 kg (baseline)\n"
              << "  Bicycle: 2.4 kg saved\n"
              << "  Electric Vehicle: 1.8 kg saved\n"
              << "  Public Transport: 1.6 kg saved\n\n"
              << "Food (per meal):\n"
              << "  Beef Dish: 0 kg (baseline)\n"
              << "  Vegetarian: 1.3 kg saved\n"
              << "  Vegan: 2.1 kg saved\n"
              << "  Local Produce: +0.5 kg saved\n\n"
              << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

// Fixed input with '?' help
float getValidatedInput(const std::string& prompt) {
    while (true) {
        std::string inputStr;
        std::cout << prompt << " (or ? for help): ";
        std::cin >> inputStr;

        if (inputStr == "?") {
            showCo2Reference();
            continue;
        }

        try {
            float input = std::stof(inputStr);
            return input;
        } catch (const std::invalid_argument&) {
            std::cout << "❌ Invalid number! Please try again.\n";
        }
    }
}

void logNewAction(ActionLogger& logger) {
    Menu typeMenu("Select Action Type");
    typeMenu.addItem("Transportation");
    typeMenu.addItem("Food Choice");

    switch (typeMenu.display()) {
        case 1: {
            std::string vehicle;
            float co2 = getValidatedInput("CO₂ saved (kg)");

            std::cin.ignore();  // Clear buffer
            std::cout << "Vehicle type (e.g., Bicycle, Electric Scooter): ";
            std::getline(std::cin, vehicle);

            logger.addAction(std::make_unique<TransportAction>(vehicle, co2));
            std::cout << "\n✅ Transportation action logged!\n";
            break;
        }
        case 2: {
            std::string meal;
            float co2 = getValidatedInput("CO₂ saved (kg)");

            std::cin.ignore();
            std::cout << "Meal description (e.g., Lentil Curry, Tofu Salad): ";
            std::getline(std::cin, meal);

            bool vegan = false;
            while (true) {
                std::cout << "Vegan? (1=Yes / 0=No): ";
                int input;
                if (std::cin >> input && (input == 0 || input == 1)) {
                    vegan = static_cast<bool>(input);
                    break;
                }
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cerr << "Invalid input! Please enter 1 or 0\n";
            }

            logger.addAction(std::make_unique<FoodChoice>(meal, vegan, co2));
            std::cout << "\n✅ Food choice logged!\n";
            break;
        }

    }
    std::cout << "\n✨ Achievement Progress Updated!\n";

    std::cin.ignore();  // Pause
}

void mainMenuLoop(UserProfile& user, Dashboard& dashboard, ActionLogger& logger) {
    Menu mainMenu("Main Menu");
    mainMenu.addItem("View Dashboard");
    mainMenu.addItem("Log New Action");
    mainMenu.addItem("Save & Exit");

    while (true) {
        switch (mainMenu.display()) {
            case 1:
                dashboard.display();
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore();
                std::cin.get();
                break;

            case 2:
                logNewAction(logger);
                break;

            case 3:
                user.saveToFile("userdata.txt");
                logger.saveToFile("actions.dat");
                return;
        }
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);  // Enable UTF-8 in Windows console
    try {
        UserProfile user("EcoWarrior");
        ActionLogger logger;
        Dashboard dashboard(user, logger);
        mainMenuLoop(user, dashboard, logger);
    } catch (const std::exception& e) {
        std::cerr << "Fatal Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
