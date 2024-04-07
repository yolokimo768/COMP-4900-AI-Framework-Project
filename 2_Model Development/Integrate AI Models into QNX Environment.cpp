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
    double cpuUsage;
    double memoryUsage;
    double temperature;
    double batteryStatus;
    double signalStrength;
};

std::vector<NetworkPerformanceMetrics> loadNetworkMetrics(const std::string& filename) {
    std::vector<NetworkPerformanceMetrics> networkMetrics;

    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return networkMetrics;
    }

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
        }
    }

    inputFile.close();
    return networkMetrics;
}

std::vector<DeviceTelemetry> loadDeviceTelemetry(const std::string& filename) {
    std::vector<DeviceTelemetry> deviceTelemetry;

    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return deviceTelemetry;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string dataType;
        iss >> dataType;

        if (dataType == "Device") {
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
        }
    }

    inputFile.close();
    return deviceTelemetry;
}

void detectAnomalies(const std::vector<DeviceTelemetry>& deviceTelemetry) {
    const double cpuThreshold = 50.0;
    for (const auto& telemetry : deviceTelemetry) {
        if (telemetry.cpuUsage > cpuThreshold) {
            std::cout << "Anomaly detected: High CPU usage" << std::endl;
        }
    }
}

void predictFuture(const std::vector<NetworkPerformanceMetrics>& networkMetrics) {

    double sumLatency = 0.0;
    double sumThroughput = 0.0;
    for (const auto& metrics : networkMetrics) {
        sumLatency += metrics.latency;
        sumThroughput += metrics.throughput;
    }
    double avgLatency = sumLatency / networkMetrics.size();
    double avgThroughput = sumThroughput / networkMetrics.size();
    double slope = 0.5;
    double intercept = avgThroughput - slope * avgLatency;

    double newLatency = 30.0;
    double predictedThroughput = slope * newLatency + intercept;
    std::cout << "Predicted future throughput for latency " << newLatency << "ms: " << predictedThroughput << "Mbps" << std::endl;
}

void integrateAIModels(const std::vector<NetworkPerformanceMetrics>& networkMetrics,
                       const std::vector<DeviceTelemetry>& deviceTelemetry) {
    detectAnomalies(deviceTelemetry);
    predictFuture(networkMetrics);
}

int main() {

    std::vector<NetworkPerformanceMetrics> networkMetrics = loadNetworkMetrics("collected_data.csv");

    std::vector<DeviceTelemetry> deviceTelemetry = loadDeviceTelemetry("collected_data.csv");

    integrateAIModels(networkMetrics, deviceTelemetry);

    return 0;
}
