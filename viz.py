import os
import numpy as np
import matplotlib.pyplot as plt

plt.rcParams['figure.dpi'] = 200
plt.rcParams['figure.figsize'] = (6, 4)

files = {
    "Euler"    : "data_euler.txt",
    "Midpoint" : "data_euler_mid.txt",
    "RK4"      : "data_rk4.txt"
}

def load_data(file, rows_to_skip=3):
    data = np.loadtxt(file, skiprows=rows_to_skip)
    t     = data[:,0]
    alpha = data[:,1]
    omega = data[:,2]
    x     = data[:,3]
    y     = data[:,4]
    Ek    = data[:,5]
    Ep    = data[:,6]
    E     = data[:,7]
    return t, alpha, omega, x, y, Ek, Ep, E

def main():
    prefix = "charts"
    os.makedirs(prefix, exist_ok=True)
    prefix += "/"
    for method_name, filename in files.items():
        t, alpha, omega, x, y, Ek, Ep, E = load_data(filename)

        plt.figure()
        plt.grid()
        plt.plot(x, y)
        plt.xlabel("x [m]")
        plt.ylabel("y [m]")
        title = f"Trajectory (x, y) - {method_name}"
        plt.title(title)
        plt.savefig(prefix + title)

        plt.figure()
        plt.grid()
        plt.plot(alpha, omega)
        plt.xlabel("alpha [rad]")
        plt.ylabel("omega [rad/s]")
        title = f"(alpha, omega) - {method_name}"
        plt.title(title)
        plt.savefig(prefix + title)

        plt.figure()
        plt.grid()
        plt.plot(t, Ek, label="Ek")
        plt.plot(t, Ep, label="Ep")
        plt.plot(t, E,  label="E")
        plt.xlabel("t [s]")
        plt.ylabel("Energy [J]")
        title = f"Energy {method_name}"
        plt.title(title)
        plt.legend()
        plt.savefig(prefix + title)
    # plt.show()

if __name__ == "__main__":
    main()