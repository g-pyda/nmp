#include <iostream>
#include <cmath>
#include <lapacke.h>
#include <vector>
#include <fstream>
#include <filesystem>

double scalar(int n, std::vector<double>& x, std::vector<double>& y) {
    double c = 0.0;

    for (int i = 0; i < n; i++) {
        c += x[i] * y[i];
    }
    return c;
}

void matr_vec_mult(int n, std::vector<double>& y, std::vector<double>& x, std::vector<double>& a) {
    for (int i = 0; i < n; i++) {
        y[i] = 0.0;
        for (int j = 0; j < n; j++) {
            y[i] += a[i*n + j] * x[j];
        } 
    }
}

void gram_schmidt(int k, std::vector<double>& y, std::vector<double>& x) {
    double c = scalar(k, y, x) / scalar(k, x, x);
    for (int i = 0; i < k; i++) {
        y[i] -= c * x[i];
    }
}

void lab() {
    srand(time(NULL));
    int n = 6;
    int itmax=150;
    double eps = pow(10.0,-8.0);

    // initializing the matrix and dispalaying it
    std::vector<double> a(n*n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                a[i*n + j] = -2.0;
            } else if (std::abs(i - j) == 1) {
                a[i*n + j] = 1.0;
            }
            std::cout << a[i*n + j] << " ";
        }
        std::cout << std::endl;
    }

    std::ofstream file_vect("eigenvectors.dat");
    std::ofstream file_val("eigenvalues.dat");

    std::vector<std::vector<double>> x(n, std::vector<double>(n, 0));
    std::vector<double> lambdas(n, 0);

    // power method
    for (int k = 0; k < n; k++) {
        // initializing the vector
        std::vector<double> x_m(n, 0);
        std::vector<double> y(n, 0);

        for (int i = 0; i < n; i++) {
            x_m[i] = ((double)rand()) / (double)RAND_MAX;
            std::cout << x_m[i] << " ";
        }
        std::cout << std::endl;

        double lambda_old = pow(10, 5);

        // opening the file to save the development of the eigenvalue
        std::ofstream file_val_dev("eigenval"+std::to_string(k)+".dat");

        for (int it = 0; it < itmax; it++) {
            matr_vec_mult(n, y, x_m, a);

            double lambda = scalar(n, x_m, y)/scalar(n, x_m, x_m);

            for(int j = 0; j < k; j++) {
                double proj = scalar(n, y, x[j]) / scalar(n, x[j], x[j]);
                for (int i = 0; i < n; i++) {
                    y[i] -= proj * x[j][i];
                }
            }

            // gram_schmidt(n, y, x_m);
            // normalizing the vector
            for (int i = 0; i < n; i++) {
                x_m[i] = y[i] / scalar(n, y, y);
            }

            file_val_dev << it << " " << lambda << std::endl;

            if (std::abs((lambda - lambda_old) / lambda) < eps) {
                break;
            }
            lambda_old = lambda;
            x_m = y;
        }

        lambdas[k] = lambda_old;
        x[k] = x_m;
        file_val_dev.close();
    }

    for (int i = 0; i < n; i++) {
        file_val << lambdas[i] << std::endl;
    }

    for (int i = 0; i < n; i++) {
        file_vect << i << " ";
        for (auto& x_m : x) {
            file_vect << x_m[i]  << " ";
        }
        file_vect << std::endl;
    }

    file_vect.close();
    file_val.close();

    std::ofstream file_arec("arec.dat");
    std::ofstream file_arec_inv("arec_inv.dat");

    std::vector<double> arec(n*n, 0);
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                arec[i*n + j] += lambdas[k] * x[k][i] * x[k][j];
            }
        }
    }

    std::vector<double> arec_inv(n*n, 0);
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                arec_inv[i*n + j] += (1.0 / lambdas[k]) * x[k][i] * x[k][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file_arec << arec[i*n + j] << " ";
        }
        file_arec << std::endl;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file_arec_inv << arec_inv[i*n + j] << " ";
        }
        file_arec_inv << std::endl;
    }
    file_arec.close();
    file_arec_inv.close();
}

void lab(int n, double eps, bool gram_schmidt) {
    srand(time(NULL));
    int itmax=150;

    // generating the case directory
    std::string case_dir = std::to_string(n) + "_" + std::to_string(eps) + "_" + (gram_schmidt ? "gram/" : "no_gram/");
    if (!std::filesystem::exists(case_dir)) {
        std::filesystem::create_directory(case_dir);
    }

    // initializing the matrix and dispalaying it
    std::vector<double> a(n*n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                a[i*n + j] = -2.0;
            } else if (std::abs(i - j) == 1) {
                a[i*n + j] = 1.0;
            }
            std::cout << a[i*n + j] << " ";
        }
        std::cout << std::endl;
    }

    std::ofstream file_vect(case_dir+"eigenvectors.dat");
    std::ofstream file_val(case_dir+"eigenvalues.dat");

    std::vector<std::vector<double>> x(n, std::vector<double>(n, 0));
    std::vector<double> lambdas(n, 0);

    // power method
    for (int k = 0; k < n; k++) {
        // initializing the vector
        std::vector<double> x_m(n, 0);
        std::vector<double> y(n, 0);

        for (int i = 0; i < n; i++) {
            x_m[i] = ((double)rand()) / (double)RAND_MAX;
        }

        double lambda_old = pow(10, 5);

        // opening the file to save the development of the eigenvalue
        std::ofstream file_val_dev(case_dir+"eigenval"+std::to_string(k)+".dat");
        

        for (int it = 0; it < itmax; it++) {
            matr_vec_mult(n, y, x_m, a);

            double lambda = scalar(n, x_m, y)/scalar(n, x_m, x_m);

            if (gram_schmidt) {
                for(int j = 0; j < k; j++) {
                    double proj = scalar(n, y, x[j]) / scalar(n, x[j], x[j]);
                    for (int i = 0; i < n; i++) {
                        y[i] -= proj * x[j][i];
                    }
                }
            }

            // gram_schmidt(n, y, x_m);
            // normalizing the vector
            for (int i = 0; i < n; i++) {
                x_m[i] = y[i] / scalar(n, y, y);
            }

            
            file_val_dev << it << " " << lambda << std::endl;
            

            if (std::abs((lambda - lambda_old) / lambda) < eps) {
                break;
            }
            lambda_old = lambda;
            x_m = y;
        }

        lambdas[k] = lambda_old;
        x[k] = x_m;
        
        file_val_dev.close();
    
    }

    for (int i = 0; i < n; i++) {
        file_val << lambdas[i] << std::endl;
    }
    if (n==200) {
        // filtering the values
        std::vector<double> indexes(10, 0);
        for (int i = 0; i < 10; i++) {
            int ind_best = 0;
            double val_best = 0;
            for (int j = 0; j < n; j++) {
                if (lambdas[j] > val_best) {
                    bool valid = true;
                    for (int k = 0; k < i; k++) {
                        if (j == indexes[k]) {
                            valid = false;
                            break;
                        }
                    }
                    if (!valid) {
                        continue;
                    }
                    val_best = lambdas[j];
                    ind_best = j;
                }
            }
            indexes[i] = ind_best;
        }
        std::cout << "The best lambdas with n=200 are: ";
        for (int i = 0; i < 10; i++) {
            std::cout << lambdas[i] << " ";
        }
    }

    for (int i = 0; i < n; i++) {
        file_vect << i << " ";
        for (auto& x_m : x) {
            file_vect << x_m[i]  << " ";
        }
        file_vect << std::endl;
    }

    file_vect.close();
    file_val.close();

    std::ofstream file_arec(case_dir+"arec.dat");
    std::ofstream file_arec_inv(case_dir+"arec_inv.dat");

    std::vector<double> arec(n*n, 0);
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                arec[i*n + j] = lambdas[k] * x[k][i] * x[k][j];
            }
        }
    }

    std::vector<double> arec_inv(n*n, 0);
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                arec_inv[i*n + j] = (1.0 / lambdas[k]) * x[k][i] * x[k][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file_arec << arec[i*n + j] << " ";
        }
        file_arec << std::endl;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file_arec_inv << arec_inv[i*n + j] << " ";
        }
        file_arec_inv << std::endl;
    }
    file_arec.close();
    file_arec_inv.close();
}