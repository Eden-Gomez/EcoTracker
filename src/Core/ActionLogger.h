#ifndef ACTIONLOGGER_H
#define ACTIONLOGGER_H

#include <vector>
#include <memory>
#include "EcoAction.h"
#include "TransportAction.h"

class ActionLogger {
private:
    std::vector<std::unique_ptr<EcoAction>> actions;
    int bikeCount = 0;

public:
    // Add these EXACT declarations
    int getTotalPoints() const;

    void addAction(std::unique_ptr<EcoAction> action)  ;
    void displayRecentActions() const;
    const std::vector<std::unique_ptr<EcoAction>>& getRecentActions() const;

//    {
//        if(dynamic_cast<TransportAction*>(action.get())) bikeCount++;
//        actions.push_back(std::move(action));
//    }

    int getTransportActionCount() const { return bikeCount; }
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    void displayRecentActions(int count = 5) const;  // Add const

    // Getters (KEEP ONLY ONE getActions DECLARATION)
    size_t getTotalActions() const { return actions.size(); }
    float getTotalCo2Saved() const;

    const std::vector<std::unique_ptr<EcoAction>>& getActions() const { return actions; }  // Only this one
};

#endif
