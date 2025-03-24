#pragma once
#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <vector>
#include <string>

class FileHandler {
public:
    static std::vector<std::vector<std::string>> readCSV(const std::string& filename);
    static void writeCSV(const std::string& filename, const std::vector<std::vector<std::string>>& data);
    static void appendCSV(const std::string& filename, const std::vector<std::string>& row);
    static bool usernameExists(const std::string& username, const std::string& filename);
};

#endif // FILEHANDLER_H