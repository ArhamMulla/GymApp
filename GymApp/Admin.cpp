#include "Admin.h"
#include "FileHandler.h"
#include "BMIUtility.h"
#include <iostream>

Admin::Admin(const std::string& username, const std::string& password)
    : User(username, password, "admin") {
}

void Admin::displayMenu() {
    std::cout << "\nAdmin Menu:\n";
    std::cout << "1. Add Trainer\n";
    std::cout << "2. Remove Trainer\n";
    std::cout << "3. View Member Payment Status\n";
    std::cout << "4. Assign Trainer to Member\n";
    std::cout << "5. View Gym Statistics\n";
    std::cout << "6. View Members\n"; 
    std::cout << "7. View Trainers\n"; 
    std::cout << "8. Reset All Data\n"; 
    std::cout << "9. Logout\n";
}

void Admin::addTrainer() {
    std::string username, password;
    int age, experience;
    std::string gender;

    std::cout << "Enter trainer username: ";
    std::getline(std::cin, username);
    std::cout << "Enter trainer password: ";
    std::getline(std::cin, password);
    std::cout << "Enter trainer age: ";
    std::cin >> age;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
    std::cout << "Enter trainer gender: ";
    std::getline(std::cin, gender);
    std::cout << "Enter trainer experience (in years): ";
    std::cin >> experience;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

    std::vector<std::string> row = { username, password, std::to_string(age), gender, std::to_string(experience) };
    FileHandler::appendCSV("data/trainers.csv", row);
    std::cout << "Trainer added successfully!\n";
}

void Admin::removeTrainer() {
    std::string username;
    std::cout << "Enter trainer username to remove: ";
    std::getline(std::cin, username);

    auto data = FileHandler::readCSV("data/trainers.csv");
    std::vector<std::vector<std::string>> updatedData;

    bool found = false;
    for (const auto& row : data) {
        if (row[0] != username) {
            updatedData.push_back(row);
        }
        else {
            found = true;
        }
    }

    if (found) {
        FileHandler::writeCSV("data/trainers.csv", updatedData);
        std::cout << "Trainer removed successfully!\n";
    }
    else {
        std::cout << "Trainer not found.\n";
    }
}

void Admin::viewMemberPaymentStatus() {
    auto data = FileHandler::readCSV("data/members.csv");

    if (data.empty()) {
        std::cout << "\nNo member data found.\n";
        return;
    }

    std::cout << "\nMember Payment Status:\n";

    for (size_t i = 1; i < data.size(); ++i) {
        const auto& row = data[i];
        if (row.size() >= 8) {
            std::cout << "Username: "  << row[0]
                << " | Membership: " << row[7] << "\n";
        }
    }
}

void Admin::assignTrainerToMember() {
    std::string memberUsername, trainerUsername;
    std::cout << "Enter member username: ";
    std::getline(std::cin, memberUsername);
    std::cout << "Enter trainer username: ";
    std::getline(std::cin, trainerUsername);

    auto members = FileHandler::readCSV("data/members.csv");
    auto trainers = FileHandler::readCSV("data/trainers.csv");

    bool memberFound = false, trainerFound = false;

    // Check if member exists
    for (const auto& row : members) {
        if (row[0] == memberUsername) {
            memberFound = true;
            break;
        }
    }

    // Check if trainer exists
    for (const auto& row : trainers) {
        if (row[0] == trainerUsername) {
            trainerFound = true;
            break;
        }
    }

    if (memberFound && trainerFound) {
        std::vector<std::string> row = { memberUsername, trainerUsername };
        FileHandler::appendCSV("data/assignments.csv", row);
        std::cout << "Trainer assigned to member successfully!\n";
    }
    else {
        std::cout << "Member or trainer not found.\n";
    }
}

void Admin::viewGymStatistics() {
    auto members = FileHandler::readCSV("data/members.csv");
    int totalMembers = members.size() - 1; // Exclude header
    int underweight = 0, normal = 0, overweight = 0, obese = 0;
    double totalBMI = 0.0;

    for (size_t i = 1; i < members.size(); ++i) { // Skip header
        double height = std::stod(members[i][3]);
        double weight = std::stod(members[i][4]);
        double bmi = BMIUtility::calculateBMI(weight, height);
        totalBMI += bmi;

        if (bmi < 18.5) underweight++;
        else if (bmi < 24.9) normal++;
        else if (bmi < 29.9) overweight++;
        else obese++;
    }

    double averageBMI = totalBMI / totalMembers;

    std::cout << "\nGym Statistics:\n";
    std::cout << "Total Members: " << totalMembers << "\n";
    std::cout << "Underweight Members: " << underweight << "\n";
    std::cout << "Normal Weight Members: " << normal << "\n";
    std::cout << "Overweight Members: " << overweight << "\n";
    std::cout << "Obese Members: " << obese << "\n";
    std::cout << "Average BMI: " << averageBMI << "\n";
}

void Admin::viewMembers() const {
    auto members = FileHandler::readCSV("data/members.csv");
    std::cout << "\nMembers:\n";

    if (members.size() > 1) {
        for (size_t i = 1; i < members.size(); ++i) {
            const auto& row = members[i];
            if (!row.empty()) {
                std::cout << "Username: " << row[0]
                    << " | Age: " << row[2]
                << " | Gender: " << row[5] << "\n";
            }
        }
    }
    else {
        std::cout << "No members found.\n";
    }
}

void Admin::viewTrainers() const {
    auto trainers = FileHandler::readCSV("data/trainers.csv");
    std::cout << "\nTrainers:\n";

    if (trainers.size() > 1) {
        for (size_t i = 1; i < trainers.size(); ++i) {
            const auto& row = trainers[i];
            if (row.size() >= 5) { // Check all fields exist
                std::cout << "Username: " << row[0]
                    << " | Experience: " << row[4] << " years"
                    << " | Gender: " << row[3] << "\n";
            }
        }
    }
    else {
        std::cout << "No trainers found.\n";
    }
}

void Admin::resetAllData() {
    // Define headers for all CSV files
    std::vector<std::vector<std::string>> membersHeader = { {"username","password","age","height","weight","gender","goal","membershipType","startDate","endDate"} };
    std::vector<std::vector<std::string>> trainersHeader = { {"username","password","age","gender","experience"} };
    std::vector<std::vector<std::string>> adminsHeader = { {"username","password"} };
    std::vector<std::vector<std::string>> assignmentsHeader = { {"memberUsername","trainerUsername"} };
    std::vector<std::vector<std::string>> workoutPlansHeader = { {"memberUsername","exercise","sets","reps","description"} };
    std::vector<std::vector<std::string>> progressHeader = { {"memberUsername","weight","bmi","achievement"} };

    // Reset files
    FileHandler::writeCSV("data/members.csv", membersHeader);
    FileHandler::writeCSV("data/trainers.csv", trainersHeader);
    FileHandler::writeCSV("data/admins.csv", adminsHeader);
    FileHandler::writeCSV("data/assignments.csv", assignmentsHeader);
    FileHandler::writeCSV("data/workout_plans.csv", workoutPlansHeader);
    FileHandler::writeCSV("data/progress.csv", progressHeader);

    std::cout << "All data reset successfully!\n";
}