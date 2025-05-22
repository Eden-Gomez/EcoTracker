#include "Menu.h"
#include <iostream>
#include <limits>  // For input handling

// ANSI color codes
#define COLOR_CYAN "\033[36m"
#define COLOR_RESET "\033[0m"

Menu::Menu(std::string header) : title(std::move(header)) {}

void Menu::addItem(const std::string& item) {
    items.push_back(item);
}

void Menu::clearScreen() const {
    std::cout << "\033[2J\033[1;1H";  // ANSI escape code for clear screen
}

int Menu::display() const {
    clearScreen();
    std::cout << COLOR_CYAN << "=== " << title << " ===\n" << COLOR_RESET;

    for(size_t i=0; i<items.size(); i++) {
        std::cout << i+1 << ") " << items[i] << "\n";
    }

    int choice;
    while(true) {
        std::cout << "\nEnter choice (1-" << items.size() << "): ";
        if(std::cin >> choice && choice >=1 && choice <= items.size()) {
            return choice;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input! Please try again.\n";
    }
}