#pragma once
#ifndef BMIUTILITY_H
#define BMIUTILITY_H

#include <string>

class BMIUtility {
public:
    static double calculateBMI(double weight, double height);
    static std::string getBMICategory(double bmi);
};

#endif // BMIUTILITY_H