#include "func.h"

int main() {

    run_and_save(euler, "../data_euler.txt", "Euler");

    run_and_save(euler_mid, "../data_euler_mid.txt", "Euler Midpoint");

    run_and_save(rk4, "../data_rk4.txt", "Runge-Kutta 4");

    return 0;
}
