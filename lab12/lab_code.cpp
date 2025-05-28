#include <complex>
#include <fftw3.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <fstream>

void gen_equidistant(double L, int n, std::vector<double>& x) {
    double delta = L / (double)n;
    for(int i = 0; i < n; i++) 
        x[i] = i*delta;
}

double noise() {
    return 10.0*((double)rand()/(double)RAND_MAX - 0.5);
}

double f_pure(double x, double omega){
    return sin(5*omega*x) + sin(15*omega*x) + sin(25*omega*x);
}

void gen_y_noised(std::vector<double>& x, std::vector<double>& y, int n, double omega) {
    for(int i = 0; i < n; i++) 
        y[i] = f_pure(x[i], omega) + noise();
}

void fast_fourier(std::vector<std::complex<double>>& in, 
    std::vector<std::complex<double>>& out, 
    int n, bool forward = true) {

    fftw_plan plan;
    if (forward)
        plan = fftw_plan_dft_1d(n, (fftw_complex *)&in[0], (fftw_complex *)&out[0], FFTW_FORWARD, FFTW_ESTIMATE);
    else
        plan = fftw_plan_dft_1d(n, (fftw_complex *)&in[0], (fftw_complex *)&out[0], FFTW_BACKWARD, FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);
}

double p_sqrt(std::complex<double> x) {
    return (pow(x.real(),2) + pow(x.imag(),2));
}

double find_max(std::vector<std::complex<double>>& y, int n) {
    double pmax = 0.0;
    for(int i = 0; i < n; i++) {
        double p = p_sqrt(y[i]);
        if ( p > pmax)
            pmax = p;
    }
    return pmax;    
}

void task(int N) {
    // generation of the noised data
    double L = 4.0, omega = 2*M_PI/L;
    std::vector<double> x(N), y(N);
    gen_equidistant(L, N, x);
    gen_y_noised(x, y, N, omega);

    std::ofstream file_noised ("./data/N"+std::to_string(N)+"f+noised.dat");
    for(int i = 0; i < N; i++)
        file_noised << x[i] << " " << f_pure(x[i], omega) << " " << y[i] << std::endl;
    file_noised.close();

    
    // FFT performance
    std::vector<std::complex<double>> in (N), out(N, std::complex<double> (0.0, 0.0)), out2(N, std::complex<double> (0.0, 0.0));
    for(int i = 0; i < N; i++) 
        in[i] = std::complex<double> (y[i], 0.0);
    fast_fourier(in, out, N);    

    std::ofstream file_re_im("./data/N"+std::to_string(N)+"re_im.dat");
    for(int i = 0; i < N; i++) 
        file_re_im << x[i] << " " << out[i].real() << " " << out[i].imag() << std::endl;
    file_re_im.close();

    
    // data denoising
    double alpha = 0.5;
    double pmax = find_max(out, N);
    for(int i = 0; i < N; i++)
        if (p_sqrt(out[i]) < alpha*pmax)
            out[i] = std::complex<double> (0.0, 0.0);

    fast_fourier(out, out2, N, false); 

    std::ofstream file_denoised("./data/N"+std::to_string(N)+"denoised.dat");
    for(int i = 0; i < N; i++)
        file_denoised << x[i] << " " << out2[i].real() / N << std::endl;
    file_denoised.close();
}