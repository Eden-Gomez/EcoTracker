#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <functional>  // For callbacks

class Menu {
private:
    std::vector<std::string> items;
    std::string title;
    void clearScreen() const;

public:
    explicit Menu(std::string header);
    void addItem(const std::string& item);
    int display() const;
};

#endif // MENU_H