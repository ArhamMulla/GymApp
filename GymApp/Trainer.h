#ifndef TRAINER_H
#define TRAINER_H

#include "User.h"
#include <string>

class Trainer : public User {
private:
    int age;
    std::string gender;
    int experience; // in years

public:
    Trainer(const std::string& username, const std::string& password, int age, const std::string& gender, int experience);

    void displayMenu() override;
    void viewAssignedMembers() const;
    void assignWorkoutPlan() const;
    void viewProgressReports() const;
};

#endif // TRAINER_H