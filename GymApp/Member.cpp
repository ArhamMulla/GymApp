#include "Member.h"
#include <iostream>

Member::Member(const std::string& username, const std::string& password, int age, double height, double weight,
    const std::string& gender, const std::string& goal, const std::string& membershipType,
    const std::string& startDate, const std::string& endDate)
    : User(username, password, "member"), age(age), height(height), weight(weight), gender(gender),
    goal(goal), membershipType(membershipType), startDate(startDate), endDate(endDate) {
}

void Member::displayMenu() {
    std::cout << "\nMember Menu:\n";
    std::cout << "1. View BMI\n";
    std::cout << "2. View Workout Plan\n";
    std::cout << "3. View Membership Details\n";
    std::cout << "4. Track Progress\n";
    std::cout << "5. Logout\n";
}

void Member::viewBMI() const {
    double bmi = BMIUtility::calculateBMI(weight, height);
    std::string category = BMIUtility::getBMICategory(bmi);
    std::cout << "\nBMI: " << bmi << " (" << category << ")\n";
}

void Member::viewWorkoutPlan() const {
    WorkoutPlan::viewWorkoutPlan(username);
}

void Member::viewMembershipDetails() const {
    std::cout << "\nMembership Details:\n";
    std::cout << "Type: " << membershipType << "\n";
    std::cout << "Start Date: " << startDate << "\n";
    std::cout << "End Date: " << endDate << "\n";
}

void Member::trackProgress() const {
    ProgressTracker::viewProgress(username);
}

// Getter for height
double Member::getHeight() const {
    return height;
}