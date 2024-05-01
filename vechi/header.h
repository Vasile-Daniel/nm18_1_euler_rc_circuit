#include <stdlib.h>
#include <malloc.h>
#include <math.h>



/*declarare tipuri*/
typedef float *vector;
typedef float **matrix;
typedef int *int_vector;
typedef int **int_matrix;
typedef struct float_complex {
    float real,imaginar;
} fcomplex;




/*header functii alocare memorie*/
vector vec(int initial, int final);
matrix matrice(int initial_linii,int final_linii,int initial_coloane,int final_coloane );
int_vector int_vec(int initial, int final);
int_matrix int_matrice(int initial_linii,int final_linii,int initial_coloane,int final_coloane );

/*header proceduri eliberare memorie*/
void free_vector(vector v, int initial, int final);
void free_matrice(matrix m, int initial_linii, int final_linii, int initial_coloane, int final_coloane);

float modul(float x); /*functie calculare modul*/  

fcomplex complex(float re, float im); //numar complex
