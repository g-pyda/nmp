#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <fstream>

enum integration_meth {Trapezoidal, Simpson, Milne};

double f(double x) {
    if (x == 0.0) return 0.0;
    return (std::sin(x) / (x * x)) * std::cos(std::sqrt(x));
}

// Trapezoidal Rule
double trapezoidal(int n, double a, double b) {
    double h = (b - a) / (n - 1);
    double sum = 0.5 * (f(a) + f(b));
    for (int i = 1; i < n - 1; ++i) {
        double xi = a + i * h;
        sum += f(xi);
    }
    return h * sum;
}

// Simpson's Rule
double simpson(int n, double a, double b) {
    if ((n - 1) % 2 != 0) return 0.0; // n must be odd
    double h = (b - a) / (n - 1);
    double sum = f(a) + f(b);
    for (int i = 1; i < n - 1; ++i) {
        double xi = a + i * h;
        sum += (i % 2 == 0 ? 2 : 4) * f(xi);
    }
    return sum * h / 3.0;
}

// Milne's Rule
double milne(int n, double a, double b) {
    if ((n - 1) % 4 != 0) return 0.0;
    double h = (b - a) / (n - 1);
    double sum = 0.0;
    for (int i = 0; i <= (n - 1 - 4); i += 4) {
        double x0 = a + i * h;
        sum += 7 * f(x0) + 32 * f(x0 + h) + 12 * f(x0 + 2 * h) + 32 * f(x0 + 3 * h) + 7 * f(x0 + 4 * h);
    }
    return (4 * h / 90.0) * sum;
}

// Romberg Method
void romberg(int pmax) {
    double a = 0, b = sqrt(180*M_PI), C_exact = -0.1433994747827965;

    std::ofstream fout("./data/romberg_"+std::to_string(pmax)+".dat");
    std::vector<std::vector<double>> R(pmax, std::vector<double>(pmax, 0.0));

    int n_nodes = 1;
    R[0][0] = 0.5 * (b - a) * (f(a) + f(b));
    fout << n_nodes << " " << std::abs(R[0][0] - C_exact) << " " << std::abs(R[0][0] - C_exact) << std::endl;

    for (int p = 1; p < pmax; ++p) {
        int n = std::pow(2, p);
        n_nodes = n + 1;
        double h = (b - a) / n;
        double sum = 0.0;
        for (int i = 1; i <= n - 1; i += 2) {
            sum += f(a + i * h);
        }
        R[p][0] = 0.5 * R[p - 1][0] + h * sum;

        for (int m = 1; m <= p; ++m) {
            R[p][m] = (std::pow(4, m) * R[p][m - 1] - R[p - 1][m - 1]) / (std::pow(4, m) - 1);
        }

        fout << n_nodes << " " << std::abs(R[p][0] - C_exact) << " " << std::abs(R[p][p] - C_exact) << std::endl;
    }

    fout.close();
}

void task(int k) {
    double a = 0, b = sqrt(180*M_PI), C_exact = -0.1433994747827965;

    std::string filename = "";
    switch (k) {
        case (integration_meth)Trapezoidal:
            filename = "trapezoidal";
            break;
        case (integration_meth)Simpson:
            filename = "simpson";
            break;
        case (integration_meth)Milne:
            filename = "milne";
            break;
        default:
            return;
    }

    std::ofstream file("./data/"+filename+".dat");

    for (int m = 10; m <= 300; ++m) {
        int n = 4 * m + 1;

        double C = 0;

        switch (k) {
            case (integration_meth)Trapezoidal:
                C = trapezoidal(n, a, b);
                break;
            case (integration_meth)Simpson:
                C = simpson(n, a, b);
                break;
            case (integration_meth)Milne:
                C = milne(n, a, b);
                break;
        }

        file << n << " " << std::fabs(C - C_exact) << std::endl;
    }
    file.close();
}