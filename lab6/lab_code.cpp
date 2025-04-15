// g++ -I ~/lapacke/lapacke/include/ -L ~/lapacke/lapacke/ main.cpp -llapacke -llapack -lblas -lm

#include <iostream>
#include "lapacke.h"
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

double scalar(int n, std::vector<double>& x, std::vector<double>& y) {
    double c = 0.0;

    for (int i = 0; i < n; i++) {
        c += x[i] * y[i];
    }

    return c;
}

void matr_vec_mult(int m, int n, std::vector<double>& x, std::vector<double>& y,
    std::vector<double>& a) {
    
    for (int i = 0; i < m; i++) {
        y[m] = 0;
        for (int j = 0; j < n; j++) 
            y[m] += x[n] * a[i*n + j];
    }
}

void task(int m, int n) {
    // name of the directory
    std::string dir = "m" + std::to_string(m) + "n" + std::to_string(n) + "/";
    // initial conditions
    double x_a = 0;
    double x_b = 3 * M_PI;

    // filling the vector x
    std::vector<double> x (m, 0);
    for (int i = 0; i < m; i++) 
        x[i] = x_a + i * (x_b - x_a) / (m-1);
    
    // filling the vector y
    std::vector<double> y (m, 0);
    for (int i = 0; i < m; i++) 
        y[i] = x[i] * cos(x[i]);

    // construction of matrix A in row-major order
    // also writing it to a file
    std::ofstream file_matrix(dir+"matrix.txt");
    std::vector<double> A (m*n, 0);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            A[i*n + j] = pow(x[i], j);
            file_matrix << A[i*n + j] << " ";
        }
        file_matrix << std::endl;
    }
    file_matrix.close();

    // constructing the arrays for singular values - s 
    std::vector<double> s (n, 0);

    // constructing the arrays for u vectors in COLUMN ORDER - u
    std::vector<double> u (n*m, 0);

    // constructing the arrays for v vectors in ROW ORDER - v
    std::vector<double> v (n*n, 0);

    // constructing the suberb vector
    std::vector<double> suberb (n, 0);

    // calculating the SVD with LAPACKE
    LAPACKE_dgesvd(LAPACK_ROW_MAJOR, 'S', 'S', m, n, &A[0], n, &s[0], &u[0], n, &v[0], n, &suberb[0]);

    // creation of singular.txt file
    std::ofstream file_sing(dir+"singular.txt");
    for (auto& s_i : s)
        file_sing << s_i << std::endl;

    file_sing.close();

    // reconstruction of the matrix A
    //and saving it to a file

    std::ofstream file_matrix_rec(dir+"matrix_rec.txt");
    std::vector<double> A_rec (m*n, 0);
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++)
                A_rec[i*n + j] += s[k] * u[i*n + k] * v[k*n + j];
            file_matrix_rec << A_rec[i*n + j] << " ";
        }
        file_matrix_rec << std::endl;
    }
    file_matrix_rec.close();

    // calculating the coefficients
    // and saving them

    std::ofstream file_coefs(dir+"coefficients.txt");

    std::vector<double> c (n, 0);
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            std::vector<double> u_k (m, 0);
            for(int j = 0; j < m; j++) 
                u_k[j] = u[j*n + k];

            std::vector<double> v_k (n, 0);
            for(int j = 0; j < n; j++)
                v_k[j] = v[j + k*n];
            
            c[i] += (1/s[k]) * v_k[i] * scalar(m, u_k, y);
        }
        file_coefs << c[i] << std::endl; 
    }
    file_coefs.close();

    std::vector<double> x_span (100, 0);
    for(int i = 0; i < 100; i++) 
        x_span[i] = x_a + i * (x_b - x_a) / 99;

    // creating the function out of the coefficients
    std::vector<double> y_test (100, 0);
    for(int i = 0; i < 100; i++)
        for(int j = 0; j < n; j++) 
            y_test[i] += c[j] * pow(x_span[i],j);

    // creating the function out of actual formula
    std::vector<double> y_actual (100, 0);
    for(int i = 0; i < 100; i++)
        y_actual[i] = x_span[i] * cos(x_span[i]);

    // creating the test points out of the coefficients
    std::vector<double> y_new (m, 0);
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++) 
            y_new[i] += c[j] * pow(x[i],j);

    // creating the plot data files
    std::ofstream file_func(dir+"functions.dat");
    for(int i = 0; i < 100; i++) 
        file_func << x_span[i] << " " << y_test[i] << " " << y_actual[i] << std::endl;

    std::ofstream file_data(dir+"data.dat");
    for(int i = 0; i < m; i++) 
        file_data << x[i] << " " << y[i] << std::endl;
    
    file_func.close();
    file_data.close();
}