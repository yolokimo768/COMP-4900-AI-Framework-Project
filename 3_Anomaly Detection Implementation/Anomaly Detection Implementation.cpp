#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include <torch/torch.h>

class LSTMModel : public torch::nn::Module {
public:
    LSTMModel(int input_size, int hidden_size, int num_layers, int output_size)
        : lstm(torch::nn::LSTMOptions(input_size, hidden_size).num_layers(num_layers).batch_first(true)),
          fc(hidden_size, output_size) {
        register_module("lstm", lstm);
        register_module("fc", fc);
    }

    torch::Tensor forward(torch::Tensor x) {
        torch::Tensor out;
        auto state = lstm->forward(x);
        out = fc->forward(std::get<0>(state).slice(1, -1, 1));
        return out;
    }

private:
    torch::nn::LSTM lstm;
    torch::nn::Linear fc;
};

std::vector<std::vector<float>> loadNetworkMetrics(const std::string& filename) {
    std::vector<std::vector<float>> networkMetrics;

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

        if (dataType == "Latency:") {
            std::vector<float> metrics;
            std::string latencyStr, throughputStr, packetLossStr, jitterStr;
            float latency, throughput, packetLoss, jitter;
            iss >> latencyStr >> latency >> throughputStr >> throughput >> packetLossStr >> packetLoss >> jitterStr >> jitter;
            metrics.push_back(latency);
            metrics.push_back(throughput);
            metrics.push_back(packetLoss);
            metrics.push_back(jitter);
            networkMetrics.push_back(metrics);
        }
    }

    inputFile.close();
    return networkMetrics;
}

torch::Tensor preprocessData(const std::vector<std::vector<float>>& metrics) {
    int seq_length = metrics.size();
    int input_size = metrics[0].size();
    auto data = torch::zeros({seq_length, 1, input_size}, torch::dtype(torch::kFloat));

    for (int i = 0; i < seq_length; ++i) {
        for (int j = 0; j < input_size; ++j) {
            data[i][0][j] = metrics[i][j];
        }
    }

    return data;
}

int main() {
    std::vector<std::vector<float>> networkMetrics = loadNetworkMetrics("collected_data.csv");

    auto data = preprocessData(networkMetrics);

    int input_size = data.size(2);
    int hidden_size = 64;
    int num_layers = 2;
    int output_size = 1;
    int seq_length = data.size(0);
    int num_epochs = 10;
    float learning_rate = 0.001;
    auto device = torch::kCPU;

    LSTMModel model(input_size, hidden_size, num_layers, output_size);
    model->to(device);
    torch::optim::Adam optimizer(model->parameters(), torch::optim::AdamOptions(learning_rate));

    for (int epoch = 0; epoch < num_epochs; ++epoch) {
        float epoch_loss = 0.0;
        for (int i = 0; i < seq_length; ++i) {
            auto inputs = data[i].unsqueeze(0).to(device);
            auto labels = torch::zeros({1, 1}, torch::dtype(torch::kFloat)).to(device); // Placeholder labels
            optimizer.zero_grad();
            auto outputs = model->forward(inputs);
            auto loss = torch::mse_loss(outputs, labels);
            loss.backward();
            optimizer.step();
            epoch_loss += loss.item<float>();
        }
        float avg_epoch_loss = epoch_loss / seq_length;
        std::cout << "Epoch [" << epoch + 1 << "/" << num_epochs << "], Average Loss: " << avg_epoch_loss << std::endl;
    }

    torch::save(model, "lstm_model.pt");

    return 0;
}
