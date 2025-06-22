#ifndef ECOTRACKER_USERPROFILE_H
#define ECOTRACKER_USERPROFILE_H

#include <string>

class UserProfile {
private:
    std::string username;
    int carbonPoints = 0;



public:
    explicit UserProfile(const std::string& name);
    void addPoints(int points);
    //    void addPoints(int points) { carbonPoints += points; };
    void displayProfile() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    int getCarbonPoints() const { return carbonPoints; } ;
    std::string getUsername() const { return username; }
};


#endif //ECOTRACKER_USERPROFILE_H
