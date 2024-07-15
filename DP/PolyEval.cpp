#include <iostream>
#include <vector>

using namespace std;

// Function to evaluate a polynomial using Horner's method
double evaluatePolynomial(const vector<double>& coefficients, double x) {
    double result = coefficients.back(); // Initialize result with the constant term

    // Evaluate polynomial using Horner's method
    for (int i = coefficients.size() - 2; i >= 0; --i) {
        result = result * x + coefficients[i];
    }

    return result;
}

// Function to evaluate polynomial at multiple points
vector<double> evaluatePolynomialAtPoints(const vector<double>& coefficients, const vector<double>& points) {
    vector<double> results;

    // Evaluate polynomial at each point
    for (double point : points) {
        double result = evaluatePolynomial(coefficients, point);
        results.push_back(result);
    }

    return results;
}

int main() {
    // Example polynomial: P(x) = 2x^3 + 3x^2 - 5x + 4
    vector<double> coefficients = {4, -5, 3, 2}; // Coefficients in ascending order of degrees

    // Points to evaluate the polynomial
    vector<double> points = {1, 2, 3, 4, 5};

    // Evaluate polynomial at the given points
    vector<double> results = evaluatePolynomialAtPoints(coefficients, points);

    // Display the results
    cout << "Polynomial Evaluation Results:" << endl;
    for (int i = 0; i < points.size(); ++i) {
        cout << "P(" << points[i] << ") = " << results[i] << endl;
    }

    return 0;
}
