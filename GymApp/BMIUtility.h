#pragma once

#include <string>

class BMIUtility {
public:
    static double calculateBMI(double weight, double height);
    static std::string getBMICategory(double bmi);
};