#include "ProgressTracker.h"
#include "FileHandler.h"
#include <iostream>

void ProgressTracker::addProgressEntry(const std::string& memberUsername, double weight, double bmi, const std::string& achievement) {
    std::vector<std::string> row = { memberUsername, std::to_string(weight), std::to_string(bmi), achievement };
    FileHandler::appendCSV("data/progress.csv", row);
    std::cout << "Progress entry added for " << memberUsername << ".\n";
}

void ProgressTracker::viewProgress(const std::string& memberUsername) {
    auto data = FileHandler::readCSV("data/progress.csv");
    std::cout << "\nProgress Report for " << memberUsername << ":\n";
    for (const auto& row : data) {
        if (row[0] == memberUsername) {
            std::cout << "Weight: " << row[1] << " kg, BMI: " << row[2] << ", Achievement: " << row[3] << "\n";
        }
    }
}