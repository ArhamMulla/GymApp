#include "WorkoutPlan.h"
#include "FileHandler.h"
#include <iostream>

void WorkoutPlan::generateWorkoutPlan(const std::string& memberUsername) {
    std::string exercise, sets, reps, description;
    std::cout << "Enter exercise: ";
    std::getline(std::cin, exercise);
    std::cout << "Enter sets: ";
    std::getline(std::cin, sets);
    std::cout << "Enter reps: ";
    std::getline(std::cin, reps);
    std::cout << "Enter description: ";
    std::getline(std::cin, description);

    std::vector<std::string> row = { memberUsername, exercise, sets, reps, description };
    FileHandler::appendCSV("data/workout_plans.csv", row);
    std::cout << "Workout plan generated for " << memberUsername << ".\n";
}

void WorkoutPlan::viewWorkoutPlan(const std::string& memberUsername) {
    auto data = FileHandler::readCSV("data/workout_plans.csv");
    for (const auto& row : data) {
        if (row[0] == memberUsername) {
            std::cout << "\nWorkout Plan:\n";
            std::cout << "Exercise: " << row[1] << "\n";
            std::cout << "Sets: " << row[2] << "\n";
            std::cout << "Reps: " << row[3] << "\n";
            std::cout << "Description: " << row[4] << "\n";
            return;
        }
    }
    std::cout << "No workout plan found for " << memberUsername << ".\n";
}