#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "FileHandler.h"
#include <vector>
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
};

#endif // ADMIN_H