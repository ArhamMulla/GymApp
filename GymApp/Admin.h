#pragma once

#include "User.h"
#include <string>

class Admin : public User {
public:
    Admin(const std::string& username, const std::string& password);

    void displayMenu() override;
    void addTrainer();
    void removeTrainer();
    void viewMemberPaymentStatus();
    void assignTrainerToMember();
    void viewGymStatistics();
    void viewMembers() const;
    void viewTrainers() const;
    static void resetAllData();
};