#include "Trainer.h"
#include "FileHandler.h"
#include "ProgressTracker.h"
#include <iostream>

Trainer::Trainer(const std::string& username, const std::string& password, int age, const std::string& gender, int experience)
    : User(username, password, "trainer"), age(age), gender(gender), experience(experience) {
}

void Trainer::displayMenu() {
    std::cout << "\nTrainer Menu:\n";
    std::cout << "1. View Assigned Members\n";
    std::cout << "2. Assign Workout Plan\n";
    std::cout << "3. View Progress Reports\n";
    std::cout << "4. Logout\n";
}

void Trainer::viewAssignedMembers() const {
    auto assignments = FileHandler::readCSV("data/assignments.csv");
    auto members = FileHandler::readCSV("data/members.csv");

    std::cout << "\nAssigned Members:\n";

    bool found = false;
    for (const auto& assignment : assignments) {
        if (assignment.size() >= 2 && assignment[1] == username) {
            std::string memberUsername = assignment[0];

            // Find member details in members.csv
            for (const auto& member : members) {
                if (member.size() >= 1 && member[0] == memberUsername) {
                    std::cout << "Username: " << member[0] << "\n";
                    std::cout << "Age: " << member[2] << "\n";
                    std::cout << "Gender: " << member[5] << "\n";
                    std::cout << "Goal: " << member[6] << "\n";
                    std::cout << "Membership Type: " << member[7] << "\n";
                    std::cout << "-------------------------\n";
                    found = true;
                    break;
                }
            }
        }
    }

    if (!found) {
        std::cout << "No members assigned to you.\n";
    }
}

void Trainer::assignWorkoutPlan() const {
    std::string memberUsername;
    std::cout << "Enter member username: ";
    std::getline(std::cin, memberUsername);

    // Check if the member exists
    auto members = FileHandler::readCSV("data/members.csv");
    bool memberExists = false;
    for (const auto& member : members) {
        if (member.size() >= 1 && member[0] == memberUsername) {
            memberExists = true;
            break;
        }
    }

    if (!memberExists) {
        std::cout << "Member not found.\n";
        return;
    }

    // Ask for workout plan details
    std::string exercise, sets, reps, description;
    std::cout << "Enter exercise: ";
    std::getline(std::cin, exercise);
    std::cout << "Enter number of sets: ";
    std::getline(std::cin, sets);
    std::cout << "Enter number of reps: ";
    std::getline(std::cin, reps);
    std::cout << "Enter description: ";
    std::getline(std::cin, description);

    // Save the workout plan to workout_plans.csv
    std::vector<std::string> row = { memberUsername, exercise, sets, reps, description };
    FileHandler::appendCSV("data/workout_plans.csv", row);
    std::cout << "Workout plan assigned to " << memberUsername << " successfully!\n";
}

void Trainer::viewProgressReports() const {
    std::string memberUsername;
    std::cout << "Enter member username: ";
    std::getline(std::cin, memberUsername);

    ProgressTracker::viewProgress(memberUsername);
}