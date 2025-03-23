#include "User.h"
#include <iostream>

User::User(const std::string& username, const std::string& password, const std::string& role)
    : username(username), password(password), role(role) {
}

std::string User::getUsername() const {
    return username;
}

std::string User::getRole() const {
    return role;
}

bool User::login(const std::string& inputUsername, const std::string& inputPassword) {
    return (username == inputUsername && password == inputPassword);
}