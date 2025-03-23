#include "BMIUtility.h"

double BMIUtility::calculateBMI(double weight, double height) {
    return weight / (height * height);
}

std::string BMIUtility::getBMICategory(double bmi) {
    if (bmi < 18.5) return "Underweight";
    else if (bmi < 24.9) return "Normal weight";
    else if (bmi < 29.9) return "Overweight";
    else return "Obese";
}