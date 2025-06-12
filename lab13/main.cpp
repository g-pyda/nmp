#include "lab_code.cpp"

int main() {
    task((integration_meth)Trapezoidal);
    task((integration_meth)Simpson);
    task((integration_meth)Milne);
    romberg(16);
}