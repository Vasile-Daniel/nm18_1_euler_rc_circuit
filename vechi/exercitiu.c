#include <stdio.h>

#define R         1000.0    // resistance R [Ohms]
#define C            0.001  // capacitance C [F]
#define E            5.0    // constant input voltage E [V] 
#define DT           0.01   // time step delta  
#define NUM_STEPS  500      // number of steps 

// Function to calculate the derivative (du/dt)
double derivative(double u) {
    return (E - u) / (R * C);
}

int main() {
    double u[NUM_STEPS]; // Array to store voltage values
    double t[NUM_STEPS]; // Array to store time values

    u[0] = 0.0; // Initialize capacitor voltage
    t[0] = 0.0; // Initialize time


    FILE *fp = NULL; 
    fp = fopen("rc_vec_data.txt", "w");

    if(fp == NULL){
        printf("Error opening the file");
        return 1;
    }

    // Iterate for a number of steps
    for (int i = 0; i < NUM_STEPS - 1; i++) {
        printf("Time: %.2f, Voltage: %.4f\n", t[i], u[i]);
        fprintf(fp, "%lf \t %lf\n", t[i], u[i]);

        double u_next = u[i] + DT * derivative(u[i]);       // Calculate the next voltage value using the explicit Euler method

        t[i+1] = t[i] + DT;                                 // Update time and voltage for the next step
        u[i+1] = u_next;
        
    }

    fclose(fp);
    // ================= GNU PLOT =========================== // 

    FILE *gnuplotPipe = NULL; 
    gnuplotPipe = popen("gnuplot -persist", "w");

    if (gnuplotPipe == NULL){
        printf("Error opening Gnuplot");
        return 1;
    }

    fprintf(gnuplotPipe, "set terminal png\n");
    fprintf(gnuplotPipe, "set output 'euler_rc_graphic_vector.png'\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set title 'Behaviour of voltage across the capacitor '\n");
    fprintf(gnuplotPipe, "set xlabel 't [s]'\n");
    fprintf(gnuplotPipe, "set ylabel 'u_C [V]'\n");

    fprintf(gnuplotPipe, "plot 'rc_vec_data.txt' using 1:2 with lines linewidth 2 linecolor rgb 'red'\n");

    fflush(gnuplotPipe);
    fprintf(gnuplotPipe, "exit\n");
    pclose(gnuplotPipe);

    return 0;
}