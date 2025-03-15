#include "lab_code.cpp"

int main() {
    lab_code();

    // report part
    lab_code_x(1.1, "coefficients1.txt", "data1.dat");
    lab_code_x(1.01, "coefficients01.txt", "data01.dat");
    lab_code_x(1.001, "coefficients001.txt", "data001.dat");
    lab_code_x(1.0001, "coefficients0001.txt", "data0001.dat");
    lab_code_x(1, "coefficients0.txt", "data0.dat");
    return 0;
}