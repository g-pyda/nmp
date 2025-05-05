#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>

double test_function(double x) {
    double res = 1 / (1 + std::pow(x,2));
    return res;
}

void gen_equidistant_x(std::vector<double>& x, double xmin, double xmax, int n) {
    double delta = (xmax - xmin) / (n - 1);
    for (int i = 0; i < n; i++) {
        x[i] = xmin + i*delta;
    }
}

void gen_chebyshev_x(std::vector<double>& x, double xmin, double xmax, int n) {
    for (int i = 0; i < n; i++) 
        x[i] = 0.5 * (xmax - xmin) * cos(M_PI*(2.0*i + 1.0)/(2.0*n + 2.0) + 0.5 * (xmin + xmax));
}

double lagrange_polynomial(std::vector<double>& x_n, std::vector<double>& y_n, int n, double x) {
    double w = 0;
    for (int j = 0; j < n; j++) {
        double alpha = 1, beta = 1;
        for (int i = 0; i < n; i++) {
            if (std::abs(i - j) > 0) {
                alpha *= (x - x_n[i]);
                beta *= (x_n[j] - x_n[i]);
            }
        }
        w += y_n[j] * alpha / beta;
    }
    return w;
}

void gen_interpolation_err(std::vector<double>& w, std::vector<double>& y, std::vector<double>& e, int n){
    for (int i = 0; i < n; i++) 
        e[i] = y[i] - w[i];
}

void task(int n, bool chebyshev) {
    // defining the endpoints
    double xmin = -5, xmax = 5;

    // generating the set of nodes and their corresponding values
    std::vector<double> x (n, 0);
    if (chebyshev) 
        gen_chebyshev_x(x, xmin, xmax, n);
    else 
        gen_equidistant_x(x, xmin, xmax, n);
    

    std::vector<double> y (n, 0);
    for (int i = 0; i < n; i++) 
        y[i] = test_function(x[i]);
    

    // generating the data for the plotting
    std::vector<double> xp (1000, 0);
    gen_equidistant_x(xp, xmin, xmax, 1000);

    std::vector<double> yp (1000, 0);
    for (int i = 0; i < 1000; i++) 
        yp[i] = test_function(xp[i]);
    
    // calculating the lagrange polynomial 
    std::vector<double> w (1000, 0);
    for (int i = 0; i < 1000; i++)
        w[i] = lagrange_polynomial(x, y, n, xp[i]);

    // calculating the error (in case of chebyshev)
    std::vector<double> err (1000,0);
    if (chebyshev)
        gen_interpolation_err(w, yp, err, 1000);

    // saving the data to a file in specified order:
    // x : y(x) : w(x) *[if chebyshev] : err(x)

    std::string filename;
    if (chebyshev)
        filename = "chebyshev";
    else
        filename = "equidistant";

    std::ofstream file("./data/" + filename + std::to_string(n-1) + ".dat");
    for (int i = 0; i < 1000; i++) {
        file << xp[i] << " " << yp[i] << " " << w[i];
        if (chebyshev) 
            file << " " << err[i];
        file << std::endl;
    }
    file.close();

    // x_node : 0
    std::ofstream file2("./data/" + filename + std::to_string(n-1) + "_nodes.dat");
    for (int i = 0; i < n; i++) 
        file2 << x[i] << " 0" << std::endl;
    file2.close();

}