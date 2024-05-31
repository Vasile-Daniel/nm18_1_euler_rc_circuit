#include <iostream>
#include <cstdio>

class EulerMethod {
public:
    double E; 
    double R;
    double C; 
    double DT; 
    int NUM_STEPS; 

    EulerMethod(double e, double r, double c, double dt, int num_steps) {
        E = e; 
        R = r;
        C = c; 
        DT = dt; 
        NUM_STEPS = num_steps; 
    }

    double derivative(double u) {
        double tau = R * C; 
        return (E - u) / tau; 
    }

    void voltage() {
        double* u = new double[NUM_STEPS]; // Array to store voltage values
        double* t = new double[NUM_STEPS]; // Array to store time values

        u[0] = 0.0; // Initialize capacitor voltage
        t[0] = 0.0; // Initialize time

        FILE* fp = fopen("rc_output_data3.txt", "w");

        if (fp == NULL) {
            std::cout << "Error opening the file" << std::endl;
            delete[] u;
            delete[] t;
            return;
        }

        for (int i = 0; i < NUM_STEPS - 1; i++) {
            std::cout << "Time: " << t[i] << ", Voltage: " << u[i] << std::endl;
            fprintf(fp, "%lf \t %lf\n", t[i], u[i]);

            double u_next = u[i] + DT * derivative(u[i]); // Calculate the next voltage value using the explicit Euler method

            t[i + 1] = t[i] + DT; // Update time and voltage for the next step
            u[i + 1] = u_next;
        }

        fclose(fp);
        delete[] u;
        delete[] t;
    }

    void figure() {
        //================ GNUPLOT ====================//

        FILE* gnuplotPipe = NULL; 
        gnuplotPipe = popen("gnuplot -persist", "w");

        if (gnuplotPipe == NULL) {
            std::cout << "Error opening Gnuplot" << std::endl;
            return; 
        }

        fprintf(gnuplotPipe, "set terminal png\n"); 
        fprintf(gnuplotPipe, "set output 'rc_euler_plot3.png'\n");
        fprintf(gnuplotPipe, "set grid\n");
        fprintf(gnuplotPipe, "set xlabel 't[s]'\n");
        fprintf(gnuplotPipe, "set ylabel 'u_c[V]'\n");
        fprintf(gnuplotPipe, "set label 'u_C(t) = E * (1 - exp(-t/tau))' at 0.124,3\n");
        fprintf(gnuplotPipe, "set title 'Euler Method applied to a RC circuit in time domain'\n");
        fprintf(gnuplotPipe, "plot 'rc_output_data3.txt' using 1:2 with lines linewidth 2 linecolor rgb 'red'\n");

        fflush(gnuplotPipe);
        fprintf(gnuplotPipe, "exit\n");
        pclose(gnuplotPipe); 
    }
};

int main() {
    double E = 5.0;
    double R = 1000.0;
    double C = 0.001;
    double DT = 0.01;
    int NUM_STEPS = 500;

    EulerMethod em(E, R, C, DT, NUM_STEPS);
    em.voltage();
    em.figure();

    return 0;
}
