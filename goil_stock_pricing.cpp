
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <random>
#include <cmath>

// Function to read data from CSV
{
    std::vector<std::vector<std::string>> data;
    std::ifstream file(goil_prices);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << goil_prices << std::endl;
        return data;
    }

    while (std::getline(goil_prices, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string value;

        while (std::getline(ss, value, ',')) {
            row.push_back(value);
        }

        data.push_back(row);
    }

    file.close();
    return data;
}

// Parameters for Geometric Brownian Motion
struct GBMParameters {
    double S0;        // Initial stock price
    double mu;        // Drift (expected return)
    double sigma;     // Volatility
    double T;         // Time horizon
    int steps;        // Number of time steps
    int simulations;  // Number of Monte Carlo simulations
};

// Function to simulate stock prices using GBM
std::vector<std::vector<double>> simulateGBM(const GBMParameters& params) 
{
    std::vector<std::vector<double>> paths(params.simulations, std::vector<double>(params.steps + 1));
    double dt = params.T / params.steps;

    // Random number generator for normal distribution
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(0.0, 1.0);

    // Simulate paths
    for (int i = 0; i < params.simulations; ++i) {
        paths[i][0] = params.S0;  // Initial price
        for (int j = 1; j <= params.steps; ++j) {
            double Z = d(gen);  // Random normal variable
            double drift = (params.mu - 0.5 * params.sigma * params.sigma) * dt;
            double diffusion = params.sigma * std::sqrt(dt) * Z;
            paths[i][j] = paths[i][j - 1] * std::exp(drift + diffusion);
        }
    }

    return paths;
}

// Main function
int main() {
    // Define parameters
    GBMParameters params{100.0, 0.05, 0.2, 1.0, 365, 1000};  // S0, mu, sigma, T, steps, simulations

    // Simulate GBM
    auto paths = simulateGBM(params);

    // Write results to a file for visualization
    std::ofstream outFile("GBM_Simulation.csv");
    for (const auto& path : paths) {
        for (const auto& price : path) {-
            outFile << price << ",";
        }
        outFile << "\n";
    }
    outFile.close();

    std::cout << "GBM simulation complete. Results saved to 'GBM_Simulation.csv'.\n";
    return 0;
}
