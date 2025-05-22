#include <iostream>

class EcoAction {
public:
    void printMessage() {
        std::cout << "My first eco class works!\n";
    }
};

int main() {
    EcoAction action;
    action.printMessage();
    return 0;
}