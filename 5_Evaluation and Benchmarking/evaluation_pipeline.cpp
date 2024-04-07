#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

std::vector<std::vector<float>> loadEvaluationData(const std::string& filePath) {
    std::vector<std::vector<float>> evaluationData;

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return evaluationData;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<float> rowData;
        std::istringstream iss(line);
        float value;
        while (iss >> value) {
            rowData.push_back(value);
        }
        evaluationData.push_back(rowData);
    }

    file.close();

    return evaluationData;
}

void evaluateAnomalyDetection(const std::vector<std::vector<float>>& evaluationData) {
    std::cout << "Anomaly detection evaluation results:" << std::endl;

    if (evaluationData.empty()) {
        std::cerr << "Evaluation data is empty." << std::endl;
        return;
    }

    float truePositives = 0, falsePositives = 0, trueNegatives = 0, falseNegatives = 0;

    for (const auto& dataRow : evaluationData) {
        if (dataRow.size() < 2) {
            std::cerr << "Invalid evaluation data format." << std::endl;
            return;
        }

        int groundTruth = static_cast<int>(dataRow[0]);
        int prediction = static_cast<int>(dataRow[1]);

        if (groundTruth == 1 && prediction == 1) {
            truePositives++;
        } else if (groundTruth == 0 && prediction == 1) {
            falsePositives++;
        } else if (groundTruth == 0 && prediction == 0) {
            trueNegatives++;
        } else if (groundTruth == 1 && prediction == 0) {
            falseNegatives++;
        }
    }

    float precision = truePositives / (truePositives + falsePositives);
    float recall = truePositives / (truePositives + falseNegatives);
    float f1Score = 2 * (precision * recall) / (precision + recall);

    std::cout << "Precision: " << std::fixed << std::setprecision(2) << precision << std::endl;
    std::cout << "Recall: " << std::fixed << std::setprecision(2) << recall << std::endl;
    std::cout << "F1-score: " << std::fixed << std::setprecision(2) << f1Score << std::endl;
}

void evaluateFuturePrediction(const std::vector<std::vector<float>>& evaluationData) {

    std::cout << "Future prediction evaluation results:" << std::endl;

    if (evaluationData.empty()) {
        std::cerr << "Evaluation data is empty." << std::endl;
        return;
    }

    float meanSquaredError = 0.0;

    for (const auto& dataRow : evaluationData) {
        if (dataRow.size() < 2) {
            std::cerr << "Invalid evaluation data format." << std::endl;
            return;
        }

        float groundTruth = dataRow[0];
        float prediction = dataRow[1];

        meanSquaredError += (prediction - groundTruth) * (prediction - groundTruth);
    }

    meanSquaredError /= evaluationData.size();

    std::cout << "Mean Squared Error: " << std::fixed << std::setprecision(2) << meanSquaredError << std::endl;
}

int main() {
    std::vector<std::vector<float>> evaluationData = loadEvaluationData("evaluation_data.csv");

    evaluateAnomalyDetection(evaluationData);

    evaluateFuturePrediction(evaluationData);

    return 0;
}
