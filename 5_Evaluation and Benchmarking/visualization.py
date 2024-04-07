import matplotlib.pyplot as plt
import numpy as np
from datetime import datetime

# Function to read evaluation results from files
def read_evaluation_results(file_path):
    dates = []
    results = []
    with open(file_path, 'r') as file:
        for line in file:
            data = line.strip().split()
            dates.append(datetime.strptime(data[0], '%Y-%m-%d'))
            results.append(float(data[1]))
    return dates, results

# Function to generate plots/graphs
def generate_plots():
    # Read evaluation results from files
    anomaly_detection_dates, anomaly_detection_results = read_evaluation_results('anomaly_detection_results.csv')
    future_prediction_dates, future_prediction_results = read_evaluation_results('future_prediction_results.csv')

    # Generate plots
    plt.figure(figsize=(10, 5))

    # Anomaly Detection Plot
    plt.subplot(1, 2, 1)
    plt.plot(anomaly_detection_dates, anomaly_detection_results, label='Anomaly Detection Results', color='blue')
    plt.xlabel('Date')
    plt.ylabel('Score')
    plt.title('Anomaly Detection')
    plt.legend()

    # Future Prediction Plot
    plt.subplot(1, 2, 2)
    plt.plot(future_prediction_dates, future_prediction_results, label='Future Prediction Results', color='green')
    plt.xlabel('Date')
    plt.ylabel('Value')
    plt.title('Future Prediction')
    plt.legend()

    # Rotate x-axis labels for better readability
    plt.xticks(rotation=45)

    # Show plots
    plt.tight_layout()
    plt.show()

# Main function
if __name__ == "__main__":
    generate_plots()
