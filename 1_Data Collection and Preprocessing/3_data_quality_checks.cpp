#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

std::vector<std::string> readDataFromFile(const std::string& filename) {
    std::vector<std::string> data;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            data.push_back(line);
        }
        file.close();
    } else {
        std::cerr << "Failed to open file: " << filename << std::endl;
    }
    return data;
}

void performDataQualityChecks(const std::vector<std::string>& data) {
    std::cout << "Performing data quality checks..." << std::endl;

    for (const auto& line : data) {

        std::regex pattern("\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2},\\d{3}");
        if (!std::regex_match(line, pattern)) {
            std::cerr << "Data quality issue detected: Invalid timestamp format - " << line << std::endl;
        }
    }
    std::cout << "Data quality checks completed." << std::endl;
}

int main() {

    std::string dataFilename = "collected_data.txt";

    std::vector<std::string> collectedData = readDataFromFile(dataFilename);

    performDataQualityChecks(collectedData);

    return 0;
}
