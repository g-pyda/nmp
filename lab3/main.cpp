#include "lab_code.cpp"
// g++ -I ~/lapacke/lapacke/include/ -L ~/lapacke/lapacke/ main.cpp -llapacke -llapack -lblas -lm

int main(int argc, char** argv) {
    lab(100, 10, "eigenvalues/ev100.dat", "eigenvalues/evex100.dat", "eigenvectors/ev100", "eigenvectors/evex100");
    lab(1000, 10, "eigenvalues/ev1000.dat", "eigenvalues/evex1000.dat", "eigenvectors/ev1000", "eigenvectors/evex1000");

    //lab(atoi(argv[0]), atof(argv[1]), "eigenvalues/ev0.txt", "eigenvectors/ev0.txt", "eigenvectors/evex0.txt");
}
    