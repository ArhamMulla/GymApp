#ifndef MEMBER_H
#define MEMBER_H

#include "User.h"
#include "BMIUtility.h"
#include "WorkoutPlan.h"
#include "ProgressTracker.h"
#include <string>
#include <ctime> // For date handling

class Member : public User {
private:
    int age;
    double height; // in meters
    double weight; // in kg
    std::string gender;
    std::string goal;
    std::string membershipType;
    std::string startDate;
    std::string endDate;

    // Helper method to calculate end date
    std::string calculateEndDate(const std::string& startDate, const std::string& membershipType);

public:
    Member(const std::string& username, const std::string& password, int age, double height, double weight,
        const std::string& gender, const std::string& goal, const std::string& membershipType);

    void displayMenu() override;
    void viewBMI() const;
    void viewWorkoutPlan() const;
    void viewMembershipDetails() const;
    void trackProgress();

    // Getter for height
    double getHeight() const;
};

#endif // MEMBER_H