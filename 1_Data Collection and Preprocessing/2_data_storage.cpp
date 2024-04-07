#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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

void storeData(const std::vector<std::string>& collectedData, const std::string& filename) {
    std::cout << "Storing collected data to file: " << filename << "..." << std::endl;
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& data : collectedData) {
            outFile << data << std::endl;
        }
        outFile.close();
        std::cout << "Data stored successfully." << std::endl;
    } else {
        std::cerr << "Failed to open file: " << filename << std::endl;
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

    std::string storageFilename = "collected_data.txt";

    storeData(collectedData, storageFilename);

    return 0;
}
