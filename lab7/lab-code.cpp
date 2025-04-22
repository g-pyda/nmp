#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>


double bissection(std::string filename, double xa, double xb, int itmax, double eps, 
    double(*f)(double)) {
        int k = 0;
        double xc, xc_before = (xa + xb) / 2, delta;

        std::ofstream file(filename + ".dat");

        do {
            xc_before = xc;
            xc = (xa + xb) / 2;
            if (f(xa)*f(xc) < 0) 
                xb = xc;
            else
                xa = xc;
            
            delta = std::abs(xa - xb);

            file << k << " " << xc << " " << std::abs(xc - xc_before) << std::endl;
            //std::cout << k << " " << itmax << " " << delta << " " << eps << std::endl;
        } while (k++ < itmax && delta > eps);

        file.close();
        return xc;
}

double secant(std::string filename, double x0, double x1, int itmax, double eps, 
    double(*f)(double)) {
        int k = 0;
        double x2, delta;

        std::ofstream file(filename + ".dat");

        do {
            x2 = x1 - f(x1) * (x1 - x0) / (f(x1) - f(x0));

            x0 = x1;
            x1 = x2;

            delta = std::abs(x1 - x0);
            file << k << " " << x1;
            if (k > 0)
                file << " " << delta;
            file << std::endl;

            //std::cout << k << " " << itmax << " " << delta << " " << eps << std::endl;
        } while (k++ < itmax && delta > eps);

        file.close();
        return x1;
}

double newton_raphson(std::string filename, double x, int itmax, double eps, 
    double(*f)(double), double(*f_der)(double)) {
        int k = 0;
        double x1, delta;

        std::ofstream file(filename + ".dat");

        do {
            x1 = x - f(x)/f_der(x);
            delta = std::abs(x1 - x);

            x = x1;
            file << k << " " << x1;
            if (k > 0)
                file << " " << delta;
            file << std::endl;

            //std::cout << k << " " << itmax << " " << delta << " " << eps << std::endl;
        } while (k++ < itmax && delta > eps);

        file.close();
        return x1;
}

double newton_raphson_modified(std::string filename, double x, int itmax, double eps, int root_degree,
    double(*f)(double), double(*f_der)(double)) {
        int k = 0;
        double x1, delta;

        std::ofstream file(filename + ".dat");

        do {
            x1 = x - double(root_degree)*f(x)/f_der(x);
            delta = std::abs(x1 - x);

            x = x1;
            file << k << " " << x1;
            if (k > 0)
                file << " " << delta;
            file << std::endl;

            //std::cout << k << " " << itmax << " " << delta << " " << eps << std::endl;
        } while (k++ < itmax && delta > eps);

        file.close();
        return x1;
}

double func(double x) {
    return (x-1)*pow(x-3, 6);
}

double func_der(double x) {
    return (pow(x-3, 6) + (x-1) * 6 * pow(x-3, 5));
}

void lab() {
    // finding the root at x = 1
    std::cout << bissection("bissection", 0.1, 1.5, 30, 1e-12, &func) << std::endl;
    std::cout << secant("secant", 0.1, 0.5, 30, 1e-12, &func) << std::endl;
    std::cout << newton_raphson("newton", 0.1, 30, 1e-12, &func, &func_der) << std::endl;

    // finding the root at x = 3
    std::cout << secant("secant3", 4.0, 6.0, 300, 1e-12, &func) << std::endl;
    std::cout << newton_raphson("newton3", 6.0, 300, 1e-12, &func, &func_der) << std::endl;

    // finding the root at x = 3 with modified newton-raphson
    std::cout << newton_raphson_modified("newton3_modified", 6.0, 300, 1e-12, 6, &func, &func_der) << std::endl;
    // finding the root at x = 1 with modified newton-raphson
    std::cout << newton_raphson_modified("newton_modified", 0.1, 30, 1e-12, 6, &func, &func_der) << std::endl;
}