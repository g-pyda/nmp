#include <iostream>
#include <string>
#include <vector>
#include "lapacke.h"
#include <cmath>
#include <fstream>

double test_function(double x) {
    return 1 / (1 + std::pow(x,2));
}

double test_sec_der(double x) {
    return (-2 + 4*std::pow(x,2) + 6*std::pow(x,4)) / (std::pow(1 + std::pow(x,2), 4));
}

void gen_equidistant_x(std::vector<double>& x, double xmin, double xmax, int n) {
    double delta = (xmax - xmin) / (n - 1);
    for (int i = 0; i < n; i++) {
        x[i] = xmin + i*delta;
    }
}

void gen_diagonal(std::vector<double>& d, int n) {
    for(int i = 0; i < n; i++) {
        if (i == 0 || i == n-1) 
            d[i] = 1;
        else d[i] = 2;
    }
}

double h_i(std::vector<double>& x, int i){
    return x[i] - x[i-1];
}

double lambda_i(std::vector<double>& x, int i) {
    return h_i(x, i+1) / (h_i(x, i+1) + h_i(x, i));
}

void gen_subdiagonal(std::vector<double>& d, std::vector<double>& x, int n, bool upper) {
    for(int i = 0; i < n-1; i++) {
        if (upper == true) {
            if (i == 0)
                d[i] = 0;
            else
                d[i] = lambda_i(x, i);
        }
        else {
            if (i == n-2)
                d[i] = 0;
            else 
                d[i] = 1 - lambda_i(x, i+1);
        }
    }
}

void gen_derivs(std::vector<double>& d, std::vector<double>& x, int n, double(*f)(double)) {
    for (int i = 0; i < n; i++) {
        if (i == 0 || i == n-1)
            d[i] = 0;
        else
            d[i] = (6 / (h_i(x,i) + h_i(x,i+1))) * ((f(x[i+1]) - f(x[i])) / h_i(x,i+1) - (f(x[i]) - f(x[i-1])) / h_i(x,i));
    }
}

void task(int n) {
    // initial conditions
    double xmin = -5.0, xmax = 5.0;
    double M = 199.0;


    std::vector<double> x_equi (n, 0);
    gen_equidistant_x(x_equi, xmin, xmax, n);

    // generation of diagonal and subdiagonals
    std::vector<double> d(n,0), du(n-1,0), dl(n-1,0);
    gen_diagonal(d, n);
    gen_subdiagonal(du, x_equi, n, true);
    gen_subdiagonal(dl, x_equi, n, false);
    // for (int i = 0; i < n; i++) {
    //     std::cout << d[i];
    //     if (i < n-1)
    //         std::cout << " " << du[i] << " " << dl[i];
    //     std::cout << std::endl;
    // }

    // generation of derivatives
    std::vector<double> derivs (n,0);
    gen_derivs(derivs, x_equi, n, test_function);
    // for (int i = 0; i < n; i++) 
    //     std::cout << derivs[i] << std::endl;
    

    // calculation of M
    LAPACKE_dgtsv(LAPACK_COL_MAJOR, n, 1, &dl[0], &d[0], &du[0], &derivs[0], n);

    // saving second derivatives to a file
    std::ofstream file_der("./data/"+std::to_string(n-1)+"der.dat");
    for(int i = 0; i < n; i++) 
        file_der << x_equi[i] << " " << derivs[i] << " " << test_sec_der(x_equi[i]) << std::endl;
    file_der.close();

    // generation of the M graph
    std::vector<double> s (M+1,0), x_M(M+1,0);
    double delta = (xmax - xmin)/M;
    for (int m = 0; m < M+1; m++) {
        double x = xmin + delta*m;
        x_M[m] = x;
        int p = -1;

        for (int i = 0; i < n; i++) {
            if (x >= x_equi[i] && x <= x_equi[i+1]) {
                p = i;
                break;
            }
        }

        if (p >= 0) {
            int i = p;
            double A = (test_function(x_equi[i+1]) - test_function(x_equi[i])) / h_i(x_equi, i+1) - h_i(x_equi, i+1)*(derivs[i+1] - derivs[i])/6;
            double B = test_function(x_equi[i]) - derivs[i]*pow(h_i(x_equi, i+1),2)/6;
            s[m] = derivs[i]*pow(x_equi[i+1] - x,3)/(6*h_i(x_equi, i+1)) + derivs[i+1]*pow(x - x_equi[i],3)/(6*h_i(x_equi, i+1)) + A*(x - x_equi[i]) + B;
        }
    }

    std::ofstream file_fun("./data/" + std::to_string(n-1) + "fun.dat");
    for(int i = 0; i < M+1; i++) 
        file_fun << x_M[i] << " " << test_function(x_M[i]) << " " << s[i] << " " << test_function(x_M[i]) - s[i] << std::endl;
    file_fun.close();
}