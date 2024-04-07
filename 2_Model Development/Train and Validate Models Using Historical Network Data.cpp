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

std::vector<NetworkPerformanceMetrics> loadHistoricalNetworkData(const std::string& filename) {
    std::vector<NetworkPerformanceMetrics> historicalData;

    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return historicalData;
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
            historicalData.push_back(metrics);
        }
    }

    inputFile.close();
    return historicalData;
}

void trainAndValidateModels(const std::vector<NetworkPerformanceMetrics>& historicalData) {

    double sumLatency = 0.0;
    double sumThroughput = 0.0;
    double sumLatencyThroughput = 0.0;
    double sumLatencySquared = 0.0;
    int n = historicalData.size();

    for (const auto& data : historicalData) {
        sumLatency += data.latency;
        sumThroughput += data.throughput;
        sumLatencyThroughput += data.latency * data.throughput;
        sumLatencySquared += data.latency * data.latency;
    }

    double beta1 = (n * sumLatencyThroughput - sumLatency * sumThroughput) / (n * sumLatencySquared - sumLatency * sumLatency);
    double beta0 = (sumThroughput - beta1 * sumLatency) / n;

    std::cout << "Learned coefficients:" << std::endl;
    std::cout << "Intercept (beta0): " << beta0 << std::endl;
    std::cout << "Slope (beta1): " << beta1 << std::endl;
}

int main() {
    std::vector<NetworkPerformanceMetrics> historicalData = loadHistoricalNetworkData("collected_data.csv");

    trainAndValidateModels(historicalData);

    return 0;
}
