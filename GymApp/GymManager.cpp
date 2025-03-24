#include "GymManager.h"
#include "Member.h"
#include "Trainer.h"
#include "Admin.h"
#include "FileHandler.h"
#include <iostream>
#include <limits> // For std::numeric_limits

void GymManager::start() {
    while (true) {
        std::cout << "\nWelcome to Gym Management System\n";
        std::cout << "1. Register\n";
        std::cout << "2. Login\n";
        std::cout << "3. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

        if (choice == 1) {
            registerUser();
        }
        else if (choice == 2) {
            loginUser();
        }
        else if (choice == 3) {
            break;
        }
        else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }
}

void GymManager::registerUser() {
    std::string role;
    std::cout << "Register as (member/trainer/admin): ";
    std::getline(std::cin, role);

    if (role != "member" && role != "trainer" && role != "admin") {
        std::cout << "Invalid role. Please try again.\n";
        return;
    }

    std::string username, password;
    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    if (FileHandler::usernameExists(username, "data/members.csv") ||
        FileHandler::usernameExists(username, "data/trainers.csv") ||
        FileHandler::usernameExists(username, "data/admins.csv")) {
        std::cout << "Error: Username already exists. Choose a different username.\n";
        return;
    }

    std::cout << "Enter password: ";
    std::getline(std::cin, password);

    if (role == "member") {
        int age;
        double heightCm, heightM, weight;
        std::string gender, goal, membershipType;

        std::cout << "Enter age: ";
        std::cin >> age;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

        std::cout << "Enter height (in centimeters): ";
        std::cin >> heightCm;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

        // Convert height from centimeters to meters
        heightM = heightCm / 100.0;

        std::cout << "Enter weight (in kg): ";
        std::cin >> weight;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

        std::cout << "Enter gender: ";
        std::getline(std::cin, gender);

        std::cout << "Enter goal: ";
        std::getline(std::cin, goal);

        std::cout << "Enter membership type (gold/silver/bronze): ";
        std::getline(std::cin, membershipType);

        if (membershipType != "gold" && membershipType != "silver" && membershipType != "bronze") {
            std::cout << "Invalid membership type. Please try again.\n";
            return;
        }

        // Create a Member object
        Member member(username, password, age, heightM, weight, gender, goal, membershipType);

        // Save member data to CSV
        std::vector<std::string> row = { username, password, std::to_string(age), std::to_string(heightM),
                                    std::to_string(weight), gender, goal, membershipType };
        FileHandler::appendCSV("data/members.csv", row);
        std::cout << "Member registered successfully!\n";
    }
    else if (role == "trainer" || role == "admin") {
        std::vector<std::string> row = { username, password, role };
        FileHandler::appendCSV((role == "trainer") ? "data/trainers.csv" : "data/admins.csv", row);
        std::cout << role << " registered successfully!\n";
    }
    else {
        std::cout << "Invalid role.\n";
    }
}

void GymManager::loginUser() {
    std::string role;
    std::cout << "Login as (member/trainer/admin): ";
    std::getline(std::cin, role);

    std::string username, password;
    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    std::cout << "Enter password: ";
    std::getline(std::cin, password);

    std::vector<std::vector<std::string>> data;
    if (role == "member") {
        data = FileHandler::readCSV("data/members.csv");
    }
    else if (role == "trainer") {
        data = FileHandler::readCSV("data/trainers.csv");
    }
    else if (role == "admin") {
        data = FileHandler::readCSV("data/admins.csv");
    }
    else {
        std::cout << "Invalid role.\n";
        return;
    }

    for (const auto& row : data) {
        if (row[0] == username && row[1] == password) {
            std::cout << "Login successful!\n";
            if (role == "member") {
                Member member(row[0], row[1], std::stoi(row[2]), std::stod(row[3]), std::stod(row[4]),
                    row[5], row[6], row[7]);
                memberMenu(member);
            }
            else if (role == "trainer") {
                Trainer trainer(row[0], row[1], 30, "male", 5); // Example values
                trainerMenu(trainer);
            }
            else if (role == "admin") {
                Admin admin(row[0], row[1]);
                adminMenu(admin);
            }
            return;
        }
    }
    std::cout << "Invalid username or password.\n";
}
void GymManager::memberMenu(Member& member) {
    while (true) {
        member.displayMenu();
        std::cout << "Choose an option: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

        switch (choice) {
        case 1:
            member.viewBMI();
            break;
        case 2:
            member.viewWorkoutPlan();
            break;
        case 3:
            member.viewMembershipDetails();
            break;
        case 4:
            member.trackProgress();
            break;
        case 5:
            member.updateProfile();
            break;
        case 6:
            member.viewProfile(); // New option
            break;
        case 7:
            std::cout << "Logging out...\n";
            return;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    }
}

void GymManager::trainerMenu(Trainer& trainer) {
    while (true) {
        trainer.displayMenu();
        std::cout << "Choose an option: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

        switch (choice) {
        case 1:
            trainer.viewAssignedMembers();
            break;
        case 2:
            trainer.assignWorkoutPlan();
            break;
        case 3: {
            std::string memberUsername;
            std::cout << "Enter member username: ";
            std::getline(std::cin, memberUsername);
            ProgressTracker::viewProgress(memberUsername);
            break;
        }
        case 4:
            std::cout << "Logging out...\n";
            return;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    }
}

void GymManager::adminMenu(Admin& admin) {
    while (true) {
        admin.displayMenu();
        std::cout << "Choose an option: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

        switch (choice) {
        case 1:
            admin.addTrainer();
            break;
        case 2:
            admin.removeTrainer();
            break;
        case 3:
            admin.viewMemberPaymentStatus();
            break;
        case 4:
            admin.assignTrainerToMember();
            break;
        case 5:
            admin.viewGymStatistics();
            break;
        case 6:
            admin.viewMembers(); 
            break;
        case 7:
            admin.viewTrainers(); 
            break;
        case 8:
            Admin::resetAllData(); // Call reset
            break;
        case 9:
            std::cout << "Logging out...\n";
            return;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    }
}