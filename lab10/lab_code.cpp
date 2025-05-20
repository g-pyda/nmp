#include <iostream>
#include <string>
#include <vector>
#include "lapacke.h"
#include <cmath>
#include <fstream>


long int factorial(long int x) {
    if (x == 0)
        return 1;
    return x * factorial(x-1);
}

double f(double x) {
    return std::exp(-1*pow(x,2));
}

double c_k(int k) {
    if (k%2 == 0)
        return pow(-1, k/2) / factorial(k/2);
    else
        return 0;
}

double R(double x, std::vector<double>& a, int n, std::vector<double>& b, int m) {
    double P = 0, Q = 0;
    for(int i = 0; i < n; i++) 
        P += a[i]*pow(x,i);
    for(int i = 0; i < m; i++) 
        Q += b[i]*pow(x,i);
    return P / Q;
}

void task(int n, int m) {
    double xmin = -5, xmax = 5;

    std::vector<double> a (n+1, 0), 
        b (m+1, 0), 
        c (m+n+1, 0),
        A (m*m, 0),
        y (m, 0),
        xplot(100, 0);
    std::vector<int> ipiv (m, 0);

    //std::cout << "c" << std::endl;
    for(int i = 0; i < n+m+1; i++) {
        c[i] = c_k(i);
        //std::cout << c[i] << std::endl;
    }
        
    
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < m; j++) {
            A[j + i*m] = c[n-m+i+j+1];
            //std::cout << A[j + i*m] << " ";
        } 
        //std::cout << std::endl;    
        y[i] = -1*c[n+1+i];
        //std::cout << y[i] << std::endl;
    }

    LAPACKE_dsysv(LAPACK_COL_MAJOR, 'U', m, 1, &A[0], m, &ipiv[0], &y[0], m);

    std::cout << "b" << std::endl;
    for(int i = 0; i < m + 1; i++) {
        if (i == 0)
            b[i] = 1;
        else
            b[i] = y[m-i];
        std::cout << b[i] << " ";
    }
        
    std::cout << std::endl << "a" << std::endl;
    for(int i = 0; i < n+1; i++) {
        double a_s = 0;
        for(int j = 0; j <= i; j++) {
            a_s += c[i-j]*b[j];
            //std::cout << i << "i " << j << "j " << c[i-j] << "c " << b[j] << "b " << a_s << std::endl;
        }
            
        a[i] = a_s;
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;

    double delta = (xmax - xmin)/(100 - 1);
    for(int i = 0; i < 100; i++) { 
        xplot[i] = xmin + i*delta;
        //std::cout << xplot[i] << std::endl;
    }

    std::ofstream file("./data/n" + std::to_string(n) + "m" + std::to_string(m) + ".dat");
    for(int i = 0; i < 100; i++) 
        file << xplot[i] << " " << f(xplot[i]) << " " << R(xplot[i], a, n+1, b, m+1) << std::endl;
    file.close();
}