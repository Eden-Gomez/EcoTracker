#include "ActionLogger.h"
#include "TransportAction.h"
#include <iostream>
#include <algorithm> // For std::min
#include <fstream>
#include <memory>


void ActionLogger::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if(!file) throw std::runtime_error("Cannot save actions");

    for(const auto& action : actions) {
        file << typeid(*action).name() << "," // Store type info
             << action->getCo2Saved() << "\n";
    }
}

void ActionLogger::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if(!file) throw std::runtime_error("Cannot load actions");

    std::string type;
    float co2;
    while(file >> type >> co2) {
        // Simplified loading - extend for real types
        if(type == "TransportAction") {
            actions.push_back(std::make_unique<TransportAction>("", co2));
        }
    }
}

void ActionLogger::addAction(std::unique_ptr<EcoAction> action) {
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
    auto start = actions.rbegin(); // Reverse iterator for newest first

    std::cout << "--- Recent Eco Actions ---\n";
    for(int i = 0; i < displayCount; ++i) {
        std::cout << i+1 << ". " << (*start)->getDetails() << "\n\n";
        ++start;
    }
}