#include <iostream>
#include <cmath>
#include <vector>
#include <cblas.h>
#include <math.h>
#include <fstream>
#include <string>

double scalar(int n, std::vector<double>& x, std::vector<double>& y) {
    double c = 0.0;

    for (int i = 0; i < n; i++) {
        c += x[i] * y[i];
    }

    return c;
}

void task1(std::string filename, double gamma) {
    int n = 2000;
    int LDA = n;

    std::vector<double> x (n, 1);
    std::vector<double> A (n*n, 0);

    std::ofstream MyFile(filename);

    // row major storage chosen
    for(int i = 0; i < n; i++) { // rows
        for(int j=0; j < n; j++) { // columns
            A[i*LDA + j] = 1/(pow(abs(i-j),4) + gamma);
        }
    }

    //multiplication of x by A^30
    for(int k=0; k < 30; k++) {
        std::vector<double> y (n, 0.0);

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                y[i] += A[i*LDA + j] * x[j];
            }
        }

        for(int i=0; i < n; i++) {
            x[i] = y[i];
        }

        double norm = scalar(n, x, x);
        std::cout << k+1 << ". " << norm << std::endl;
        MyFile << k+1 << ". " << norm << std::endl;
    }

    MyFile.close();
}

void task2() {
    int n = 5;
    int LDA = n;

    std::vector<double> A (n*n, 0);

    std::ofstream MyFile("task2.txt");

    // row major storage chosen
    for(int i = 0; i < n; i++) { // rows
        for(int j=0; j < n; j++) { // columns
            A[i*LDA + j] = 1/(pow(abs(i-j),4) + 2);
        }
    }

    std::vector<double> C (n*n, 0);

    for(int i=0; i < n; i++) {
        for(int k=0; k < n; k++) {
            double s = 0;
            for(int j=0; j < n; j++) {
                s += A[i*LDA + j] * A[j*LDA + k];
            }
            C[i*LDA + k] = s;
        }
    }

    for(int i=0; i < n; i++) {
        for(int j=0; j < n; j++) {
            std::cout << C[i*LDA + j] << "\t";
            MyFile << C[i*LDA + j] << "\t";
        }
        std::cout << std::endl;
        MyFile << std::endl;
    }

    MyFile.close();
}

int main() {
    //task1("task1_gamma2.txt", 2.0);
    //task1("task1_gamma3.txt", 3.0);
    task2();
}