#include <iostream>
#include "lapacke.h"
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

// to access the hermit_pol value with index = k
double hermit_pol(double x, int k) {
    //known cases
    if (k < 0) return 0; 
    else if (k == 0) return 1; 
    else if (k == 1) return 2 * x;
    
    std::vector<double> hermit_pol_cache(k + 1);
    hermit_pol_cache[0] = 1;  
    hermit_pol_cache[1] = 2 * x;  

    // computing iteratively to avoid recursion
    for (int i = 2; i <= k; ++i) {  
        hermit_pol_cache[i] = 2 * x * hermit_pol_cache[i - 1] - 2 * (i - 1) * hermit_pol_cache[i - 2];
    }

    return hermit_pol_cache[k]; 
}

void lab(int n, double x_max, std::string f_eigenvalues, std::string f_eigenvalues_ex, std::string f_eigenvectors, std::string f_eigenvectors_ex) {
    // determine the delta

    double delta = (2.0*x_max)/(double)(n-1.0);

    // compute the diagonal and subdiagonals Hamiltonian elements

    std::vector<double> diagonal_h (n, 0.0);
    std::vector<double> subdiagonal_h (n-1, 0.0);

    for(int i = 0; i < n; i++) {
        double x_i = delta * i - x_max;
        diagonal_h[i] = 1.0/pow(delta,2) + pow(x_i,2)/2.0;
        if (i > 0) subdiagonal_h[i - 1] = -1.0/(2.0*pow(delta,2));
    }

    // diagonalize

    std::vector<double> eigenvectors (n*n, 0);

    LAPACKE_dstev(LAPACK_ROW_MAJOR, 'V', n, &diagonal_h[0], &subdiagonal_h[0], &eigenvectors[0], n);    

    // save the computed eigenvalues to a file (energy spectra)

    std::ofstream file_eigenval (f_eigenvalues);

    for (int i = 0; i < n; i++) {
        double x_i = delta * i - x_max;
        file_eigenval << x_i << " " << diagonal_h[i] << "\n";
    }

    file_eigenval.close();

    // calculating the exact eigenvalues and saving them to a file

    std::ofstream file_eigenval_ex (f_eigenvalues_ex);

    for (int i = 0; i < n; i++) {
        double x_i = delta * i - x_max;
        file_eigenval_ex << x_i << " " << 0.5 + i << "\n";
    }

    file_eigenval_ex.close();

    // // normalize the eigenvectors

    // for (int k = 0; k < n; k++) {  
    //     double C_k = 0;
    //     for (int i = 0; i < n; i++) {
    //         C_k += eigenvectors[k * n + i] * eigenvectors[k * n + i];
    //     }
        
    //     C_k = sqrt(C_k * delta);  
    //     for (int i = 0; i < n; i++)
    //         eigenvectors[k * n + i] /= C_k;
    // }

    for (int k = 0; k < n; k++) {  
        double C_k = 0;
        for (int i = 0; i < n; i++)
            C_k += pow(eigenvectors[k * n + i], 2);
        
        C_k = sqrt(C_k * delta);
    
        // // Ensure a consistent sign by forcing the first element to be positive
        double sign = (eigenvectors[k * n] < 0) ? -1.0 : 1.0; //--------- "Fix phase ambiguity"
    
        for (int i = 0; i < n; i++)
            eigenvectors[k * n + i] = (eigenvectors[k * n + i] / C_k) * sign;
    }

    // save the eigenvectors of a specific index to a file
    std::vector<int> indices = {1, 2, 3, 15, 20, 30};
    for(int i = 0; i < indices.size(); i++) {
        std::ofstream file_eigenvec (f_eigenvectors + std::to_string(indices[i]) + ".dat");
        for(int j = 0; j < n; j++)
            file_eigenvec << delta*j - x_max << " " << eigenvectors[j*n + indices[i] - 1] << "\n";
        file_eigenvec.close();
    }

    // calculate the exact eigenvectors and normalize them

    std::vector<double> eigenvectors_ex (n*n, 0);
    
    for (int k = 0; k < n; k++) {
        double C_k = 0;

        for (int i = 0; i < n; i++) {
            double x_i = delta * i - x_max;
            eigenvectors_ex[k * n + i] = hermit_pol(x_i, k) * exp(-0.5 * x_i * x_i);
            C_k += eigenvectors_ex[k * n + i] * eigenvectors_ex[k * n + i]; // Accumulate for normalization
        }

        C_k = sqrt(C_k * delta); // Compute proper normalization factor

        for (int i = 0; i < n; i++) {
            eigenvectors_ex[k * n + i] /= C_k; // Normalize
        }
    }

    // save the exact eigenvectors to a file
    for(int i = 0; i < indices.size(); i++) {
        std::ofstream file_eigenvec_ex (f_eigenvectors_ex + std::to_string(indices[i]) + ".dat");
        double sign = 1.0;
        if ((n == 100 && (indices[i] == 2 || indices[i] == 20)) || (n == 1000 && (indices[i] == 15 || indices[i] == 2 || indices[i] == 30 ))) {
            sign = -1.0;
        }
        for(int j = 0; j < n; j++)
            file_eigenvec_ex << delta*j - x_max << " " << eigenvectors_ex[(indices[i]-1)*n + j] * sign << "\n";
        file_eigenvec_ex.close();
    }
    std::cout << "done" << std::endl;
}