

#include <iostream>
#include "lapacke.h"
#include <vector>
#include <fstream>

int main() {
    int n = 6;
    int lda = n;
    int ldb = 1;
    std::vector<int> ipiv (n, 0);

    double x0 = 0, x1 = 1, x2 = 2, x3 = 3;
    std::vector<double> A = {
        1, x0, pow(x0,2), pow(x0,3), pow(x0,4), pow(x0,5),
        0, 1, 2*x0, 3*pow(x0,2), 4*pow(x0,3), 5*pow(x0,4),
        1, x1, pow(x1,2), pow(x1,3), pow(x1,4), pow(x1,5),
        1, x2, pow(x2,2), pow(x2,3), pow(x2,4), pow(x2,5),
        1, x3, pow(x3,2), pow(x3,3), pow(x3,4), pow(x3,5),
        0, 1, 2*x3, 3*pow(x3,2), 4*pow(x3,3), 5*pow(x3,4)
    };

    std::cout << "Matrix A at the start" << std::endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            std::cout << A[i*n + j] << ", ";
        }
        std::cout << std::endl;
    }

    std::vector<double> b = {0, 1, 1, 0, -1, 0};

    LAPACKE_dgetrf(LAPACK_ROW_MAJOR, n, n, &A[0], lda, &ipiv[0]);
    LAPACKE_dgetrs(LAPACK_ROW_MAJOR, 'N', n, 1, &A[0], lda, &ipiv[0], &b[0], ldb);


    std::cout << "Matrix A after the LU decomposition" << std::endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            std::cout << A[i*n + j] << ", ";
        }
        std::cout << std::endl;
    }

    double det = 0;
    for(int i = 0; i < n; i++)
        det*= A[i*n + i];

    std::cout << "Determinant: " << det << std::endl;

    std::ofstream file ("coefficients.txt");

    for(int i = 0; i < n; i++) {
        std::cout << b[i] << " ";
        file << b[i] << std::endl;
    }

    std::cout << std::endl;

    file.close();


    std::ofstream data ("data.dat");

    double xmin = 0, xmax = 3.0;
    double delta = (xmax - xmin)/100;

    for(int i=0; i < 100; i++) {
        double x = xmin + i*delta;
        double p = 0;

        for(int j=0; j < 5; j++) {
            p+= b[j]*pow(x,j);
        }

        data << x << " " << p << "\n";

    }

    data.close();
}