#include "FileHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<std::vector<std::string>> FileHandler::readCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for reading.\n";
        return {};
    }
    std::vector<std::vector<std::string>> data;
    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        data.push_back(row);
    }
    if (data.empty()) {
        std::cerr << "Warning: File " << filename << " is empty.\n";
    }
    return data;
}

void FileHandler::writeCSV(const std::string& filename, const std::vector<std::vector<std::string>>& data) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing.\n";
        return;
    }
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) file << ",";
        }
        file << "\n";
    }
}

void FileHandler::appendCSV(const std::string& filename, const std::vector<std::string>& row) {
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for appending.\n";
        return;
    }
    for (size_t i = 0; i < row.size(); ++i) {
        file << row[i];
        if (i < row.size() - 1) file << ",";
    }
    file << "\n";
}

bool FileHandler::usernameExists(const std::string& username, const std::string& filename) {
    auto data = readCSV(filename);
    for (const auto& row : data) {
        if (!row.empty() && row[0] == username) {
            return true;
        }
    }
    return false;
}