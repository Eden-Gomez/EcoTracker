#ifndef ACTIONLOGGER_H
#define ACTIONLOGGER_H

#include "EcoAction.h"
#include <memory>
#include <vector>

/**
 * Manages storage and retrieval of eco actions
 * Uses smart pointers for automatic memory management
 */
class ActionLogger {
private:
    std::vector<std::unique_ptr<EcoAction>> actions;

public:
    void addAction(std::unique_ptr<EcoAction> action);
    void displayRecentActions(int count = 5) const;
    float getTotalCo2Saved() const;

public:
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif // ACTIONLOGGER_H