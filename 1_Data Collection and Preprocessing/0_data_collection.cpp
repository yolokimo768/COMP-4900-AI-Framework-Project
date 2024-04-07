#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

struct DataSource {
    std::string name;
    std::string endpoint;
};

void collectData(const DataSource& dataSource, std::vector<std::string>& collectedData) {
    std::cout << "Collecting data from " << dataSource.name << "..." << std::endl;
    std::ifstream file(dataSource.endpoint);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            collectedData.push_back(line);
        }
        file.close();
    } else {
        std::cerr << "Failed to open file: " << dataSource.endpoint << std::endl;
    }
}

void preprocessData(std::vector<std::string>& collectedData) {
    std::cout << "Preprocessing data..." << std::endl;

    for (std::string& data : collectedData) {
        std::transform(data.begin(), data.end(), data.begin(), ::tolower);
    }
}

int main() {
	
    std::vector<DataSource> dataSources = {
        {"Network Performance Metrics", "network_metrics.txt"},
        {"Device Telemetry", "device_telemetry.txt"},
        {"Event Logs", "event_logs.txt"}
    };

    std::vector<std::string> collectedData;

    for (const auto& dataSource : dataSources) {
        collectData(dataSource, collectedData);
    }

    preprocessData(collectedData);

    std::cout << "Preprocessed Data:" << std::endl;
    for (const auto& data : collectedData) {
        std::cout << data << std::endl;
    }

    return 0;
    }