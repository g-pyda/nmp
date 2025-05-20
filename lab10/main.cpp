// g++ -I ~/lapacke/lapacke/include/ -L ~/lapacke/lapacke/ main.cpp -llapacke -llapack -lblas -lm
#include "lab_code.cpp"

int main() {
    task(2, 2);
    task(4, 4);
    task(6, 6);
    task(2, 4);
    task(2, 6);
    task(2, 8);
}