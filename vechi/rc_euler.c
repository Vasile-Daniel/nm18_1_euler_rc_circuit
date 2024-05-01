#include <stdio.h>

// Definim constantele pentru rezistență (R) și capacitate (C)
#define R 1000.0
#define C 0.001

// Definim tensiunea de intrare constantă (E)
#define E 5.0

// Definim pasul de timp (Δt)
#define DT 0.01

// Funcție pentru calculul derivatei (du/dt)
double derivative(double u) {
    return (E - u) / (R * C);
}

int main() {
    double u = 0.0; // Inițializăm tensiunea pe condensator
    double t = 0.0; // Inițializăm timpul

    FILE *fp = NULL;
    fp = fopen("rc_data.txt", "w");
    if (fp == NULL){
        printf("Error opening the file");
        return 1;
    } 
    // Iterăm pentru un număr de pași
    for (int i = 0; i < 500; i++) {
        printf("Timp: %.2f, Tensiune: %.4f\n", t, u);
        fprintf(fp, "%lf\t %lf\n", t,u);
        
        // Calculăm următoarea valoare a tensiunii folosind metoda Euler explicită
        double u_next = u + DT * derivative(u);
        
        // Actualizăm timpul și tensiunea pentru următorul pas
        t += DT;
        u = u_next;
    }

    return 0;
}