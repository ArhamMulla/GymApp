#pragma once
#include <string>
#include <vector>

class User {
protected:
    std::string username;
    std::string password;
    std::string role;

public:
    User(const std::string& username, const std::string& password, const std::string& role);
    virtual ~User() = default;

    std::string getUsername() const;
    std::string getRole() const;

    virtual void displayMenu() = 0; // Pure virtual function
    bool login(const std::string& inputUsername, const std::string& inputPassword);
};