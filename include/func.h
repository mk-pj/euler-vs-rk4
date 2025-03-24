#ifndef FUNC_H
#define FUNC_H

#include <cmath>

#define g 9.81
#define L 2.0
#define m 1.5
#define h 0.08
#define T 10.0
#define alfa0 (45 * M_PI / 180)
#define omega0 0.0

using std::sin, std::cos;

typedef void calc_step(const double*, double, double*);

void pendulum(const double*, double*);

void euler(const double*, double, double*);

void euler_mid(const double*, double, double*);

void rk4(const double*, double, double*);

double kinetic_energy(double);

double potential_energy(double);

double total_energy(double, double);

double x_pos(double);

double y_pos(double);

void run_and_save(calc_step, const char*, const char*);

#endif
