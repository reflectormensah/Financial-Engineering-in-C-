#include <iostream>
#include <cmath>
#include <random>
#include <Eigen/Dense>

// Constants
const double beta = 0.99;  // Discount factor
const double sigma = 1.0;  // Risk aversion
const double phi = 1.5;    // Taylor rule coefficient
const double rho = 0.8;    // Persistence of monetary shock
const double sigma_e = 0.01; // Std deviation of shock

using namespace Eigen;
using namespace std;

// Function to simulate the DSGE model
void simulateDSGE(int periods) {
    VectorXd inflation(periods);
    VectorXd interest_rate(periods);
    VectorXd output_gap(periods);
    VectorXd shock(periods);

    // Generate random shocks
    default_random_engine generator;
    normal_distribution<double> distribution(0.0, sigma_e);

    // Initial conditions
    inflation(0) = 0.0;
    interest_rate(0) = 0.0;
    output_gap(0) = 0.0;
    shock(0) = distribution(generator);

    // Simulate New Keynesian DSGE model using Euler equations
    for (int t = 1; t < periods; t++) {
        shock(t) = rho * shock(t-1) + distribution(generator); // AR(1) shock
        interest_rate(t) = phi * inflation(t-1) + shock(t);    // Taylor Rule
        output_gap(t) = (interest_rate(t) - inflation(t)) / sigma; // IS curve
        inflation(t) = beta * inflation(t-1) + output_gap(t); // Phillips curve
    }

    // Print results
    cout << "Period | Inflation | Interest Rate | Output Gap" << endl;
    for (int t = 0; t < periods; t++) {
        cout << t << " | " << inflation(t) << " | " << interest_rate(t) << " | " << output_gap(t) << endl;
    }
}

// Main function
int main() {
    int periods = 50; // Simulation horizon
    simulateDSGE(periods);
    return 0;
}
