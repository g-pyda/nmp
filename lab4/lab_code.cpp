// g++ -I ~/lapacke/lapacke/include/ -L ~/lapacke/lapacke/ main.cpp -lm -O3

#include <iostream>
#include "lapacke.h"
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <random>

double scalar(int n, std::vector<double>& x, std::vector<double>& y) {
    double c = 0.0;

    for (int i = 0; i < n; i++) {
        c += x[i] * y[i];
    }

    return c;
}

void matr_vec_mult_CSR(int n, std::vector<double>& x, std::vector<double>& y,
    std::vector<double>& a, std::vector<int>& col, std::vector<int>& row) {
    
    for (int i = 0; i < n; i++) {
        y[i] = 0;
        for (int l = row[i]; l < row[i+1]; l++) {
            int j = col[l];
            y[i] += a[l]*x[j];
        }
    }
}

void SOR(int n, double omega, std::vector<double>& v,
    std::vector<double>& a, std::vector<int>& col, std::vector<int>& row,
    std::vector<double> ro, std::vector<double> d) {
    for (int i = 0; i < n; i++) {
        double c = 0.0;
        for(int l = row[i]; l < row[i+1]; l++) {
            int j = col[l];
            c+= a[l]*v[j];
        }
        v[i] = v[i] + (omega/d[i]) * (ro[i] - c);
    }

}

void lab(double omega) {
    std::string directory = "omega"+std::to_string(int(omega*100))+"/";
    // initial conditions
    int n = 500;
    int nnz_max = 3*n;
    double delta = 1.0;
    int itmax = 10000;
    double eps = pow(10.0, -15.0);

    std::vector<double> ro (n, 0.0);

    for(int i = 0; i < n; i++) 
        ro[i] = 0.1 * pow(sin((2*i*M_PI)/(n-1)), 10.0);
    
    //calculation of matrix A
    std::vector<double> a (nnz_max, 0);
    std::vector<int> col (nnz_max, 0);
    std::vector<int> row (n+1, 0);
    std::vector<double> d (n);

    int nnz = 0;

    for (int i = 0; i < n; i++) {
        row[i] = -1;

        if(i > 0) {
            a[nnz] = 1/pow(delta,2.0);
            col[nnz] = i - 1;
            row[i] = nnz;
            nnz++;
        }

        a[nnz] = -2/pow(delta, 2.0);
        d[i] = a[nnz];
        col[nnz] = i;
        if (row[i] < 0)
            row[i] = nnz;
        nnz++;

        if (i < n - 1) {
            a[nnz] = 1/pow(delta, 2.0);
            col[nnz] = i + 1;
            nnz++;
        }
    }

    row[n] = nnz;
 
    std::vector<double> v (n, 1);

    std::ofstream file_norms (directory+"norms.dat");


    int k = 0;
    double norm_v = 0.0;
    do {
        k++;

        SOR(n, omega, v, a, col, row, ro, d);

        std::vector<double> res (n);
        matr_vec_mult_CSR(n, v, res, a, col, row);
        for(int i = 0; i < n; i++) 
            res[i] = ro[i] - res[i];

        double norm_r = sqrt(scalar(n, res, res));
        std::cout << norm_r << std::endl;
        norm_v = sqrt(scalar(n, v, v));
        file_norms << k << " " << norm_v << " " << norm_r << std::endl;
    } while (k < itmax && norm_v > eps);

    file_norms.close();

    std::ofstream file_vect (directory+"vector.dat");

    for(int i = 0; i < n; i++) {
        double x = delta*i;
        file_vect << x << " " << ro[i] << " " << v[i] << std::endl;
    }

    file_vect.close();
}

void lab_add(bool rand) {
    std::string directory;
    if (rand) {
        directory = "rand/";
    }
    else {
        directory = "zeroes/";
    }
    double omega = 1.99;
    // initial conditions
    int n = 500;
    int nnz_max = 3*n;
    double delta = 1.0;
    int itmax = 10000;
    double eps = pow(10.0, -8.0);

    std::vector<double> ro (n, 0.0);

    for(int i = 0; i < n; i++) 
        ro[i] = 0.1 * pow(sin((2*i*M_PI)/(n-1)), 10.0);
    
    //calculation of matrix A
    std::vector<double> a (nnz_max, 0);
    std::vector<int> col (nnz_max, 0);
    std::vector<int> row (n+1, 0);
    std::vector<double> d (n);

    int nnz = 0;

    for (int i = 0; i < n; i++) {
        row[i] = -1;

        if(i > 0) {
            a[nnz] = 1/pow(delta,2.0);
            col[nnz] = i - 1;
            row[i] = nnz;
            nnz++;
        }

        a[nnz] = -2/pow(delta, 2.0);
        d[i] = a[nnz];
        col[nnz] = i;
        if (row[i] < 0)
            row[i] = nnz;
        nnz++;

        if (i < n - 1) {
            a[nnz] = 1/pow(delta, 2.0);
            col[nnz] = i + 1;
            nnz++;
        }
    }

    row[n] = nnz;

    std::vector<double> v(n, 0);  

    if (rand) {  
        for (int i = 0; i < n; i++) {
            v[i] = 100.0 * static_cast<double>(std::rand()) / RAND_MAX;  
        }
    }

    std::ofstream file_norms (directory+"norms.dat");


    int k = 0;
    double norm_v = 0.0;
    do {
        k++;

        SOR(n, omega, v, a, col, row, ro, d);

        std::vector<double> res (n);
        matr_vec_mult_CSR(n, v, res, a, col, row);
        for(int i = 0; i < n; i++) 
            res[i] = ro[i] - res[i];

        double norm_r = sqrt(scalar(n, res, res));
        std::cout << norm_r << std::endl;
        norm_v = sqrt(scalar(n, v, v));
        file_norms << k << " " << norm_v << " " << norm_r << std::endl;
    } while (k < itmax && norm_v > eps);

    file_norms.close();

    std::ofstream file_vect (directory+"vector.dat");

    for(int i = 0; i < n; i++) {
        double x = delta*i;
        file_vect << x << " " << ro[i] << " " << v[i] << std::endl;
    }

    file_vect.close();
}