#pragma once

#include "User.h"
#include "Member.h"
#include "Trainer.h"
#include "Admin.h"
#include "FileHandler.h"

class GymManager {
public:
    void start(); // Main function to start the application

private:
    void registerUser(); // Function to handle user registration
    void loginUser();    // Function to handle user login

    // Role-specific menu functions
    void memberMenu(Member& member);   // Menu for members
    void trainerMenu(Trainer& trainer); // Menu for trainers
    void adminMenu(Admin& admin);      // Menu for admins
    std::string getPasswordInput();
};
