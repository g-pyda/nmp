// g++ -I ~/lapacke/lapacke/include/ -L ~/lapacke/lapacke/ main.cpp -lm

#include "lab.cpp"

int main() {
    lab();
    lab(200, 1e-8, true);
    lab(6, 1e-4, true);
    lab(6, 1e-8, false);
}