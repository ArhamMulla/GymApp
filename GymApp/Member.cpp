#include "Member.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

Member::Member(const std::string& username, const std::string& password, int age, double height, double weight,
    const std::string& gender, const std::string& goal, const std::string& membershipType)
    : User(username, password, "member"), age(age), height(height), weight(weight), gender(gender),
    goal(goal), membershipType(membershipType) {
    // Set start date to the current date
    time_t now = time(0);
    tm localTime;
    localtime_s(&localTime, &now); // Use localtime_s instead of localtime
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d");
    startDate = oss.str();

    // Calculate end date based on membership type
    endDate = calculateEndDate(startDate, membershipType);
}

std::string Member::calculateEndDate(const std::string& startDate, const std::string& membershipType) {
    // Parse the start date
    std::tm startTm = {};
    std::istringstream iss(startDate);
    iss >> std::get_time(&startTm, "%Y-%m-%d");

    // Calculate the duration based on membership type
    int durationMonths = 0;
    if (membershipType == "gold") {
        durationMonths = 12; // 1 year
    }
    else if (membershipType == "silver") {
        durationMonths = 8; // 8 months
    }
    else if (membershipType == "bronze") {
        durationMonths = 4; // 4 months
    }

    // Add the duration to the start date
    startTm.tm_mon += durationMonths;
    mktime(&startTm); // Normalize the date

    // Format the end date
    std::ostringstream oss;
    oss << std::put_time(&startTm, "%Y-%m-%d");
    return oss.str();
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

void Member::trackProgress() {
    double newWeight;
    std::string achievement;
    std::cout << "Enter current weight (in kg): ";
    std::cin >> newWeight;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
    std::cout << "Enter achievement: ";
    std::getline(std::cin, achievement);

    // Update the member's weight
    weight = newWeight;

    // Calculate BMI and add progress entry
    double bmi = BMIUtility::calculateBMI(weight, height);
    ProgressTracker::addProgressEntry(username, weight, bmi, achievement);
}

// Getter for height
double Member::getHeight() const {
    return height;
}