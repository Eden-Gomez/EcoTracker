#include "ActionLogger.h"
#include "TransportAction.h"
#include "FoodChoice.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <memory>
#include <filesystem>
#include <sstream>

int ActionLogger::getTotalPoints() const {
    int total = 0;
    for(const auto& action : actions) {
        total += action->calculatePoints();
    }
    return total;
}
const std::vector<std::unique_ptr<EcoAction>>& ActionLogger::getRecentActions() const {
    return actions;
}


void ActionLogger::saveToFile(const std::string& filename) const {
    std::filesystem::create_directories(
            std::filesystem::path(filename).parent_path()
    );

    std::ofstream file(filename);
    if(!file) throw std::runtime_error("Cannot save actions");

    for(const auto& action : actions) {
        if(auto* transport = dynamic_cast<TransportAction*>(action.get())) {
            file << "TransportAction" << ","
                 << transport->getVehicle() << ","
                 << transport->getCo2Saved() << "\n";
        }
        else if(auto* food = dynamic_cast<FoodChoice*>(action.get())) {
            file << "FoodChoice" << ","
                 << food->getMealType() << ","
                 << (food->isVeganMeal() ? "1" : "0") << ","
                 << food->getCo2Saved() << "\n";
        }
    }
}

void ActionLogger::loadFromFile(const std::string& filename) {
    if(!std::filesystem::exists(filename)) return;

    std::ifstream file(filename);
    if(!file) throw std::runtime_error("Cannot load actions");

    std::string line;
    while(std::getline(file, line)) {
        std::istringstream ss(line);
        std::string type;

        std::getline(ss, type, ',');

        if(type == "TransportAction") {
            std::string vehicle;
            float co2;
            std::getline(ss, vehicle, ',');
            ss >> co2;
            actions.push_back(std::make_unique<TransportAction>(vehicle, co2));
        }
        else if(type == "FoodChoice") {
            std::string meal, veganStr;
            float co2;
            std::getline(ss, meal, ',');
            std::getline(ss, veganStr, ',');
            ss >> co2;
            bool vegan = (veganStr == "1");
            actions.push_back(std::make_unique<FoodChoice>(meal, vegan, co2));
        }
    }
}

void ActionLogger::addAction(std::unique_ptr<EcoAction> action) {
    if (dynamic_cast<TransportAction*>(action.get())) {
        bikeCount++;
    }
    actions.push_back(std::move(action));
}


float ActionLogger::getTotalCo2Saved() const {
    float total = 0.0f;
    for(const auto& action : actions) {
        total += action->getCo2Saved();
    }
    return total;
}

void ActionLogger::displayRecentActions(int count) const {
    if(actions.empty()) {
        std::cout << "No actions logged yet!\n";
        return;
    }

    int displayCount = std::min(count, static_cast<int>(actions.size()));
    auto start = actions.rbegin();

    std::cout << "--- Recent Eco Actions ---\n";
    for(int i = 0; i < displayCount; ++i) {
        std::cout << i+1 << ". " << (*start)->getDetails() << "\n\n";
        ++start;
    }
}