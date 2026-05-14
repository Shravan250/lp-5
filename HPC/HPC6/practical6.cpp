#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <omp.h>

using namespace std;

// Function to remove commas from numbers like "1,234.56"
string removeCommas(string str)
{
    string result = "";

    for (char ch : str)
    {
        if (ch != ',')
        {
            result += ch;
        }
    }

    return result;
}

// Function to load CSV data
void loadCSV(string filename, vector<double>& openPrice, vector<double>& closePrice)
{
    ifstream file(filename);

    string line;

    // Skip header line
    getline(file, line);

    while (getline(file, line))
    {
        stringstream ss(line);

        string date, open, high, low, close, volume;

        getline(ss, date, ',');
        getline(ss, open, ',');
        getline(ss, high, ',');
        getline(ss, low, ',');
        getline(ss, close, ',');
        getline(ss, volume, ',');

        // Remove commas if present
        open = removeCommas(open);
        close = removeCommas(close);

        // Store Open price as input feature
        openPrice.push_back(stod(open));

        // Store Close price as output target
        closePrice.push_back(stod(close));
    }

    file.close();
}

int main()
{
    vector<double> x; // Open prices
    vector<double> y; // Close prices

    // Load training dataset
    loadCSV("Google_Stock_Price_Train.csv", x, y);

    int n = x.size();

    // Linear Regression Parameters
    double weight = 0.0;
    double bias = 0.0;

    double learning_rate = 0.000001;
    int epochs = 1000;

    // Training using Gradient Descent
    for (int epoch = 0; epoch < epochs; epoch++)
    {
        double dw = 0.0;
        double db = 0.0;

        // Parallel computation using OpenMP
#pragma omp parallel for reduction(+ : dw, db)
        for (int i = 0; i < n; i++)
        {
            // Predicted value
            double prediction = weight * x[i] + bias;

            // Error calculation
            double error = prediction - y[i];

            // Gradient calculation
            dw += error * x[i];
            db += error;
        }

        // Average gradients
        dw = dw / n;
        db = db / n;

        // Update parameters
        weight = weight - learning_rate * dw;
        bias = bias - learning_rate * db;
    }

    cout << "Training Completed Successfully\n";

    cout << "\nLearned Weight: " << weight << endl;
    cout << "Learned Bias: " << bias << endl;

    // Predict stock closing price
    double inputPrice;

    cout << "\nEnter Open Price to Predict Close Price: ";
    cin >> inputPrice;

    double predictedClose = weight * inputPrice + bias;

    cout << "Predicted Close Price: " << predictedClose << endl;

    return 0;
}