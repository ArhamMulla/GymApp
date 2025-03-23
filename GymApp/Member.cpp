#include "Member.h"
#include "FileHandler.h"
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
    std::cout << "5. Update Profile\n";
    std::cout << "6. View Profile\n"; // New option
    std::cout << "7. Logout\n";
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

void Member::updateProfile() {
    while (true) {
        std::cout << "\nUpdate Profile:\n";
        std::cout << "1. Update Age\n";
        std::cout << "2. Update Height\n";
        std::cout << "3. Update Weight\n";
        std::cout << "4. Update Gender\n";
        std::cout << "5. Update Goal\n";
        std::cout << "6. Update Membership Type\n";
        std::cout << "7. Return to Main Menu\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

        switch (choice) {
        case 1: {
            std::cout << "Enter new age: ";
            std::cin >> age;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
            break;
        }
        case 2: {
            double heightCm;
            std::cout << "Enter new height (in centimeters): ";
            std::cin >> heightCm;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
            height = heightCm / 100.0; // Convert to meters
            break;
        }
        case 3: {
            std::cout << "Enter new weight (in kg): ";
            std::cin >> weight;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
            break;
        }
        case 4: {
            std::cout << "Enter new gender: ";
            std::getline(std::cin, gender);
            break;
        }
        case 5: {
            std::cout << "Enter new goal: ";
            std::getline(std::cin, goal);
            break;
        }
        case 6: {
            std::cout << "Enter new membership type (gold/silver/bronze): ";
            std::getline(std::cin, membershipType);
            // Update end date based on new membership type
            endDate = calculateEndDate(startDate, membershipType);
            break;
        }
        case 7: {
            // Save updated profile to members.csv
            std::vector<std::vector<std::string>> members = FileHandler::readCSV("data/members.csv");
            for (auto& row : members) {
                if (row[0] == username) {
                    row[2] = std::to_string(age); // Update age
                    row[3] = std::to_string(height); // Update height
                    row[4] = std::to_string(weight); // Update weight
                    row[5] = gender; // Update gender
                    row[6] = goal; // Update goal
                    row[7] = membershipType; // Update membership type
                    break;
                }
            }
            FileHandler::writeCSV("data/members.csv", members);
            std::cout << "Profile updated successfully!\n";
            return; // Return to main menu
        }
        default: {
            std::cout << "Invalid choice. Try again.\n";
            break;
        }
        }
    }
}

// Getter for height
double Member::getHeight() const {
    return height;
}

void Member::viewProfile() const {
    std::cout << "\nProfile Details:\n";
    std::cout << "Username: " << username << "\n";
    std::cout << "Age: " << age << "\n";
    std::cout << "Height: " << height << " m\n";
    std::cout << "Weight: " << weight << " kg\n";
    std::cout << "Gender: " << gender << "\n";
    std::cout << "Goal: " << goal << "\n";
    std::cout << "Membership Type: " << membershipType << "\n";
    std::cout << "Start Date: " << startDate << "\n";
    std::cout << "End Date: " << endDate << "\n";
}

