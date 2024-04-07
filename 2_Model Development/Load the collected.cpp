#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

struct NetworkPerformanceMetrics {
    double latency;
    double throughput;
    double packetLoss;
    double jitter;
};

struct DeviceTelemetry {
    int cpuUsage;
    int memoryUsage;
    int temperature;
    int batteryStatus;
    int signalStrength;
};

struct EventLog {
    std::string timestamp;
    std::string description;
};

int main() {

    std::ifstream inputFile("collected_data.csv");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open collected_data.csv" << std::endl;
        return 1;
    }

    std::vector<NetworkPerformanceMetrics> networkMetrics;
    std::vector<DeviceTelemetry> deviceTelemetry;
    std::vector<EventLog> eventLogs;

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string dataType;
        iss >> dataType;

        if (dataType == "Network") {
            NetworkPerformanceMetrics metrics;
            iss.ignore(256, ':');
            iss >> metrics.latency;
            iss.ignore(256, ':');
            iss >> metrics.throughput;
            iss.ignore(256, ':');
            iss >> metrics.packetLoss;
            iss.ignore(256, ':');
            iss >> metrics.jitter;
            networkMetrics.push_back(metrics);
        } else if (dataType == "Device") {
            DeviceTelemetry telemetry;
            iss.ignore(256, ':');
            iss >> telemetry.cpuUsage;
            iss.ignore(256, ':');
            iss >> telemetry.memoryUsage;
            iss.ignore(256, ':');
            iss >> telemetry.temperature;
            iss.ignore(256, ':');
            iss >> telemetry.batteryStatus;
            iss.ignore(256, ':');
            iss >> telemetry.signalStrength;
            deviceTelemetry.push_back(telemetry);
        } else if (dataType == "Event") {
            EventLog log;
            std::getline(iss, log.timestamp, '-');
            std::getline(iss, log.description);
            eventLogs.push_back(log);
        }
    }

    inputFile.close();

    std::cout << "Network Performance Metrics:" << std::endl;
    for (const auto& metrics : networkMetrics) {
        std::cout << "Latency: " << metrics.latency << "ms" << std::endl;
        std::cout << "Throughput: " << metrics.throughput << "Mbps" << std::endl;
        std::cout << "Packet Loss: " << metrics.packetLoss << "%" << std::endl;
        std::cout << "Jitter: " << metrics.jitter << "ms" << std::endl;
        std::cout << std::endl;
    }

    std::cout << "Device Telemetry:" << std::endl;
    for (const auto& telemetry : deviceTelemetry) {
        std::cout << "CPU Usage: " << telemetry.cpuUsage << "%" << std::endl;
        std::cout << "Memory Usage: " << telemetry.memoryUsage << "%" << std::endl;
        std::cout << "Temperature: " << telemetry.temperature << "°C" << std::endl;
        std::cout << "Battery Status: " << telemetry.batteryStatus << "%" << std::endl;
        std::cout << "Signal Strength: " << telemetry.signalStrength << "dBm" << std::endl;
        std::cout << std::endl;
    }

    std::cout << "Event Logs:" << std::endl;
    for (const auto& log : eventLogs) {
        std::cout << log.timestamp << " - " << log.description << std::endl;
    }

    return 0;
}
