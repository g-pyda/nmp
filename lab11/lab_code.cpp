#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <fstream>

double scalar(int n, std::vector<double>& x, std::vector<double>& y) {
    double res = 0;
    for(int i = 0; i < n; i++) 
        res += x[i]*y[i];
    return res;
}

double p(double x, std::vector<double>& a) {
    return a[0]*std::atan(a[1]*x + a[2]) + a[3];
}

double del() {
    return 0.1 * (((double)std::rand()/RAND_MAX) - 0.5);
}

void gen_equidistant(double xmin, double xmax, int n, std::vector<double>& result) {
    double delta = (xmax - xmin) / (n-1);
    for(int i = 0; i < n; i++) 
        result[i] = xmin + i*delta;
}

void gen_y(std::vector<double>& x, std::vector<double>& a, std::vector<double>& y, int n) {
    for (int i = 0; i < n; i++) 
        y[i] = p(x[i], a) + del();
}

void gen_y_p(std::vector<double>& x, std::vector<double>& a, std::vector<double>& y, int n) {
    for (int i = 0; i < n; i++) 
        y[i] = p(x[i], a);
}

void gen_grad_p(double x, std::vector<double>& a, std::vector<double>& g) {
    g[0] = std::atan(a[1]*x + a[2]);
    g[1] = (a[0]*x)/(pow(a[1]*x + a[2], 2) + 1);
    g[2] = (a[0])/(pow(a[1]*x + a[2], 2) + 1);
    g[3] = 1;
}

double f(int n, std::vector<double>& x, std::vector<double>& y, std::vector<double>& w, std::vector<double>& a) {
    double res = 0;
    for(int i = 0; i < n; i++)
        res += w[i]*pow(y[i] - p(x[i], a), 2);
    return res;
}

void gen_grad_f(int n, std::vector<double>& x, std::vector<double>& y, 
    std::vector<double>& w, std::vector<double>& a, std::vector<double>& g) {

    g = {0.0, 0.0, 0.0, 0.0};
    for(int i = 0; i < n; i++) {
        std::vector<double> grad (4, 0.0);
        gen_grad_p(x[i], a, grad);
        for(int j = 0; j < 4; j++)
            g[j] = g[j] - 2*w[i]*(y[i] - p(x[i], a))*grad[j]; 
    }
}

double goldenSection(int n, std::vector<double>& x, std::vector<double>& y, 
    std::vector<double>& w, std::vector<double>& a, std::vector<double>& u, double lambda_b) {
    double lambda, lambda_a = 0.0, r = 0.618, eps = pow(10, -5.0);
    for(int l = 0; l < 100 && fabs(lambda_b - lambda_a) > eps; l++) {
        double lambda1 = lambda_a + pow(r, 2)*(lambda_b -lambda_a),
            lambda2 = lambda_a + r*(lambda_b -lambda_a);
        std::vector<double> a1 (4, 0.0), a2 (4, 0.0);
        for(int i = 0; i < 4; i++) {
            a1[i] = a[i] + lambda1*u[i];
            a2[i] = a[i] + lambda2*u[i];
        }
        if (f(n, x, y, w, a1) > f(n, x, y, w, a2))
            lambda_a = lambda1;
        else    
            lambda_b = lambda2;
        lambda = (lambda_a + lambda_b) / 2.0;
    }
    return lambda;
}

void conjugateGradient(int n, std::vector<double>& x, std::vector<double>& y, 
    std::vector<double>& w, std::vector<double>& a, bool Fletcher, double lambda_b) {

    double eps_a = pow(10.0,-4.0), s = 100;
    std::vector<double> g (4, 0.0), g_old (4, 0.0), u (4, 0.0), 
        a_old (4, 0.0), a_diff (4, 0.0);

    for(int k = 0; k < 1000 && s > eps_a; k++) {
        gen_grad_f(n, x, y, w, a, g);
        for(int i = 0; i < 4; i++) 
            g[i] = -1*g[i];

        if (k==0)
            u = g;
        else {
            double gamma;
            if (Fletcher)
                gamma = std::sqrt(fabs(scalar(4, g, g) / scalar(4, g_old, g_old)));
            else {
                std::vector<double> g_diff (4, 0.0);
                for(int i = 0; i < 4; i++) 
                    g_diff[i] = g[i] - g_old[i];
                std::cout << "g_diff = " << g_diff[0] << " " << g_diff[1] << " "
                    << g_diff[2] << " " << g_diff[3] << std::endl;
                gamma = std::sqrt(fabs(scalar(4, g_diff, g) / scalar(4, g_old, g_old)));
            }
            for(int i = 0; i < 4; i++) 
                u[i] = g[i] + gamma*u[i];
        }
        for(int i = 0; i < 4; i++) 
            g_old[i] = g[i];

        double lambda = goldenSection(n, x, y, w, a, u, lambda_b);
        for(int i = 0; i < 4; i++) 
            a_old[i] = a[i];
        for(int i = 0; i < 4; i++) {
            a[i] = a[i] + lambda*u[i];
            a_diff[i] = a[i] - a_old[i];
        }
        s = scalar(4, a_diff, a_diff);
    }
}

void task(bool Fletcher, double lambda_b = 0.1, bool largerA = false) {
    double xmin = -10, xmax = 20;
    int n = 100;

    std::vector<double> x (n,0), y (n,0), y_p_exact(n,0), y_p_fit(n,0), w(n,1.0),
        a_exact = {0.5, 10.0, -30.0, 0.7}, a = {1.0, 1.0, 1.0, 1.0};
    if (largerA) {
        a[0] = 10.0;
        a[1] = 20.0;
        a[2] = -60.0;
        a[3] = 7.0;
    }
    gen_equidistant(xmin, xmax, n, x);
    gen_y(x, a_exact, y, n);
    gen_y_p(x, a_exact, y_p_exact, n);

    conjugateGradient(n, x, y, w, a, Fletcher, lambda_b);
    std::cout << "a = " << a[0] << " " << a[1] << " " << a[2] << " " << a[3] << std::endl;
    gen_y_p(x, a, y_p_fit, n);

    std::string filename = "";
    if (Fletcher)
        filename = "Fletcher_";
    else
        filename = "Polak_";
    filename += std::to_string(lambda_b);
    if (largerA)
        filename += "_largerA";
    std::ofstream file ("./data/" + filename + ".dat");
    for(int i = 0; i < n; i++) 
        file << x[i] << " " << y[i] << " " << y_p_exact[i] << " " << y_p_fit[i] << std::endl;
    file.close();
}