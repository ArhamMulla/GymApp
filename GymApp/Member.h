#ifndef MEMBER_H
#define MEMBER_H

#include "User.h"
#include "BMIUtility.h"
#include "WorkoutPlan.h"
#include "ProgressTracker.h"

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

public:
    Member(const std::string& username, const std::string& password, int age, double height, double weight,
        const std::string& gender, const std::string& goal, const std::string& membershipType,
        const std::string& startDate, const std::string& endDate);

    void displayMenu() override;
    void viewBMI() const;
    void viewWorkoutPlan() const;
    void viewMembershipDetails() const;
    void trackProgress() const;

    // Getter for height
    double getHeight() const;
};

#endif // MEMBER_H