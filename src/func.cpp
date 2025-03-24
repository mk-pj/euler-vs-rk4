#include <fstream>
#include "func.h"

void pendulum(const double *y, double *dy_dt) {
    const double alfa = y[0];
    const double omega = y[1];
    dy_dt[0] = omega;
    dy_dt[1] = -(g/L) * sin(alfa);
}

void euler(const double *y, const double dt, double *y_out) {
    double dy_dt[2];
    pendulum(y, dy_dt);
    y_out[0] = y[0] + dt * dy_dt[0];
    y_out[1] = y[1] + dt * dy_dt[1];
}

void euler_mid(const double *y, const double dt, double *y_out) {
    double k1[2], k2[2];
    pendulum(y, k1);

    double y_mid[2];
    y_mid[0] = y[0] + 0.5 * dt * k1[0];
    y_mid[1] = y[1] + 0.5 * dt * k1[1];

    pendulum(y_mid, k2);

    y_out[0] = y[0] + dt * k2[0];
    y_out[1] = y[1] + dt * k2[1];
}

void rk4(const double *y, const double dt, double *y_out) {
    double y_temp[2];
    double k1[2], k2[2], k3[2], k4[2];
    pendulum(y, k1);

    y_temp[0] = y[0] + 0.5*dt*k1[0];
    y_temp[1] = y[1] + 0.5*dt*k1[1];
    pendulum(y_temp, k2);

    y_temp[0] = y[0] + 0.5*dt*k2[0];
    y_temp[1] = y[1] + 0.5*dt*k2[1];
    pendulum(y_temp, k3);

    y_temp[0] = y[0] + dt*k3[0];
    y_temp[1] = y[1] + dt*k3[1];
    pendulum(y_temp, k4);

    y_out[0] = y[0] + dt * (k1[0] + 2*k2[0] + 2*k3[0] + k4[0])/6;
    y_out[1] = y[1] + dt * (k1[1] + 2*k2[1] + 2*k3[1] + k4[1])/6;
}

double kinetic_energy(const double omega) {
    return 0.5 * m * (L*L) * (omega*omega);
}

double potential_energy(const double alfa) {
    return m * g * L * (1 - cos(alfa));
}

double total_energy(const double alfa, const double omega) {
    return potential_energy(alfa) + kinetic_energy(omega);
}

double x_pos(const double alfa) {
    return L * sin(alfa);
}

double y_pos(const double alfa) {
    return -L * cos(alfa);
}

void run_and_save(calc_step func, const char *file_name, const char *method) {
    constexpr int n = static_cast<int>(T/h);
    double y[2] = { alfa0, omega0 };
    double t = 0;
    std::fstream file(file_name, std::ios::out | std::ios::trunc);

    file << "# " << method << " method\n";
    file << "# h = " << h << ", T = " << T << "\n";
    file << "# t  alfa  omega  x  y  Ek  Ep  E\n";

    for(int i = 0; i <= n; i++) {
        const double alfa = y[0];
        const double omega = y[1];

        const double Ek = kinetic_energy(omega);
        const double Ep = potential_energy(alfa);
        const double E  = Ek + Ep;
        const double x  = x_pos(alfa);
        const double yy = y_pos(alfa);

        file << t << " "
             << alfa << " "
             << omega << " "
             << x << " "
             << yy << " "
             << Ek << " "
             << Ep << " "
             << E << "\n";

        double y_next[2];
        func(y, h, y_next);

        y[0] = y_next[0];
        y[1] = y_next[1];
        t += h;
    }
    file.close();
}
