#include <iostream>
#include "Core/EcoAction.h"
#include "Core/TransportAction.h"
#include "Core/UserProfile.h"

int main() {
    // Base class action
    EcoAction recycling("Plastic Recycling", 2.3f);
    std::cout << recycling.getDetails() << "\n\n";

    // Derived class action
    TransportAction bikeCommute("Bicycle", 1.8f);
    std::cout << bikeCommute.getFullDetails() << std::endl;

    try {
        UserProfile user("EcoWarrior");
        user.addPoints(150);
        user.saveToFile("userdata.txt");

        UserProfile loadedUser("");
        loadedUser.loadFromFile("userdata.txt");
        loadedUser.displayProfile();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}