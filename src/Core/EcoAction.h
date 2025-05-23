#ifndef ECOACTION_H
#define ECOACTION_H

#include <string>
#include <ctime>

class EcoAction {
protected:
    std::string actionName;
    float co2Saved;
    std::time_t timestamp;

public:
    EcoAction(std::string name, float co2);

    virtual std::string getDetails() const = 0;  // PURE VIRTUAL

    int calculatePoints() const;
    std::string getTimestamp() const;
    float getCo2Saved() const { return co2Saved; }

    virtual ~EcoAction() = default;
};

#endif // ECOACTION_H
