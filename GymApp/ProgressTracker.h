#pragma once

#include <string>
#include <vector>

class ProgressTracker {
public:
    static void addProgressEntry(const std::string& memberUsername, double weight, double bmi, const std::string& achievement);
    static void viewProgress(const std::string& memberUsername);
};