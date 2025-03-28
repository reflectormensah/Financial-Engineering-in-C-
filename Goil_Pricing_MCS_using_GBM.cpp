#include <string>
#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <numeric>
#include <vector>

using namespace std;

//Simulating stock price paths
double monteCarloStockPrice(double S0, double r, double sigma, double T, int numSimulations, int steps) 
{
    // Initialize random number generator for normal distribution
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> d(0.0, 1.0); // Gaussian distribution
    
    double dt = T / steps; // Time step
    vector<double> finalPrices(numSimulations); // Store final stock prices for each simulation

    for (int i = 0; i < numSimulations; ++i) {
        double S = S0; // Initialize stock price for this simulation
        for (int j = 0; j < steps; ++j) {
            double Z = d(gen); // Generating random normal variable
            S *= exp((r - 0.5 * sigma * sigma) * dt + sigma * sqrt(dt) * Z);
        }
        finalPrices[i] = S; // Store the final price
    }

    // Calculate the average of final prices
    double sum = accumulate(finalPrices.begin(), finalPrices.end(), 0.0);
    return sum / numSimulations;
}

int main() {
    // Input parameters
    double S0 = 1.51;     // Initial stock price
    double r = 0.2982;       // Risk-free rate
    double sigma = 0.1046;    // Volatility
    double T = 4.0;        // Time of forecast (next years starting from 2024)
    int numSimulations = 100000; // Number of simulations
    int steps = 252;       // Number of steps (in a year)

    // Perform Monte Carlo simulation
    double expectedPrice = monteCarloStockPrice(S0, r, sigma, T, numSimulations, steps);

    // Output the result
    cout << "Monte Carlo Estimated Stock Price: " << expectedPrice << endl;

    return 0;
}
