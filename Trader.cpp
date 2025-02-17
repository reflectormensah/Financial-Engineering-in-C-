#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

// Function to calculate the mean and standard deviation

void mean_stddev(vector<double> &data, double &mean, double &stddev)
{
    double sum = 0;
    for (int i = 0; i < data.size(); i++)
    {
        sum += data[i];
    }
    mean = sum / data.size();
    double sq_sum = 0;
    for (int i = 0; i < data.size(); i++)
    {
        sq_sum += (data[i] - mean) * (data[i] - mean);
    }
    stddev = sqrt(sq_sum / data.size());
}

// Function to calculate the correlation coefficient

double correlation_coefficient(vector<double> &x, vector<double> &y)
{
    double mean_x, mean_y, stddev_x, stddev_y;
    mean_stddev(x, mean_x, stddev_x);
    mean_stddev(y, mean_y, stddev_y);
    double covariance = 0;
    for (int i = 0; i < x.size(); i++)
    {
        covariance += (x[i] - mean_x) * (y[i] - mean_y);
    }
    return covariance / (x.size() * stddev_x * stddev_y);
}

// Function to calculate the covariance matrix

MatrixXd covariance_matrix(vector<vector<double>> &data)
{
    MatrixXd cov(data[0].size(), data[0].size());
    for (int i = 0; i < data[0].size(); i++)
    {
        for (int j = 0; j < data[0].size(); j++)
        {
            vector<double> x, y;
            for (int k = 0; k < data.size(); k++)
            {
                x.push_back(data[k][i]);
                y.push_back(data[k][j]);
            }
            cov(i, j) = correlation_coefficient(x, y);
        }
    }
    return cov;
}   