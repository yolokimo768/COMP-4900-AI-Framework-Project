#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

int main() {
    std::ifstream inputFile("collected_data.txt");

    std::ofstream outputFile("collected_data.csv");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open collected_data.txt" << std::endl;
        return 1;
    }

    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to create collected_data.csv" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::replace(line.begin(), line.end(), '\t', ',');

        outputFile << line << std::endl;
    }

    inputFile.close();
    outputFile.close();

    std::cout << "Conversion completed successfully." << std::endl;

    return 0;
}
