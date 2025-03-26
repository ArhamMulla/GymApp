#pragma once

#include <string>
#include <vector>

class WorkoutPlan {
public:
    static void generateWorkoutPlan(const std::string& memberUsername);
    static void viewWorkoutPlan(const std::string& memberUsername);
};