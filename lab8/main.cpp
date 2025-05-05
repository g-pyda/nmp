#include "lab_code.cpp"

int main() {
    //task for equidistant nodes
    task(5+1, false);
    task(10+1, false);
    task(20+1, false);

    //task for chebyshev nodes
    task(20+1, true);
    task(30+1, true);
}