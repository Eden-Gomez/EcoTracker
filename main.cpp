#include <iostream>
#include "src/Core/EcoAction.h"
#include "src/Core/TransportAction.h"

int main() {
    // Base class action
    EcoAction recycling("Plastic Recycling", 2.3f);
    std::cout << recycling.getDetails() << "\n\n";

    // Derived class action
    TransportAction bikeCommute("Bicycle", 1.8f);
    std::cout << bikeCommute.getFullDetails() << std::endl;

    return 0;
}