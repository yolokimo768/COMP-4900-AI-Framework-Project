#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

int main() {

    std::string networkMetricsFile = "network_metrics.txt";
    std::string deviceTelemetryFile = "device_telemetry.txt";
    std::string eventLogsFile = "event_logs.txt";

    std::cout << "Network Performance Metrics:" << std::endl;
    std::vector<std::string> networkMetricsData = readDataFromFile(networkMetricsFile);
    for (const auto& line : networkMetricsData) {
        std::cout << line << std::endl;
    }

    std::cout << "\nDevice Telemetry:" << std::endl;
    std::vector<std::string> deviceTelemetryData = readDataFromFile(deviceTelemetryFile);
    for (const auto& line : deviceTelemetryData) {
        std::cout << line << std::endl;
    }

    std::cout << "\nEvent Logs:" << std::endl;
    std::vector<std::string> eventLogsData = readDataFromFile(eventLogsFile);
    for (const auto& line : eventLogsData) {
        std::cout << line << std::endl;
    }

    return 0;
}
