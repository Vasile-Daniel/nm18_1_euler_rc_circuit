#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include "header.h"

/*functia alocare vector*/
vector vec(int initial, int final)
{
    vector v;
    v=(float*)malloc((unsigned)(final-initial+1)*sizeof(float));
    if (!v)
        printf("Eroare de alocare vector");
    return v-initial;
}

/*vector intreg alocare memorie*/
int_vector int_vec(int initial, int final)
{
    int_vector v;
    v=(int*)malloc((unsigned)(final-initial+1)*sizeof(int));
    if (!v)
        printf("Eroare de alocare vector");
    return v-initial;
}

/*functia alocare matrice*/
matrix matrice(int initial_linii,int final_linii,int initial_coloane,int final_coloane)
{
    int i;
    matrix m;
    m=(float **)malloc((unsigned)(final_linii-initial_linii+1)*sizeof(float *));
    if (!m)
        printf("Eroare de alocare matrice");
    m=m-initial_linii;
    for (i=initial_linii; i<=final_linii; i++)
    {
        m[i]=(float *)malloc((unsigned)(final_coloane-initial_coloane+1)*sizeof(float));
        if (!m[i])
            printf("Eroare de alocare matrice");
        m[i]=m[i]-initial_coloane;
    }
  return m;    
}

/*matrice de tip intreg alocare memmorie*/
int_matrix int_matrice(int initial_linii,int final_linii,int initial_coloane,int final_coloane )
{
    int i;
    int_matrix m;
    m=(int **)malloc((unsigned)(final_linii-initial_linii+1)*sizeof(int *));
    if (!m)
        printf("Eroare de alocare matrice");
    m=m-initial_linii;
    for (i=initial_linii; i<=final_linii; i++)
    {
        m[i]=(int *)malloc((unsigned)(final_coloane-initial_coloane+1)*sizeof(int));
        if (!m[i])
            printf("Eroare de alocare matrice");
        m[i]=m[i]-initial_coloane;
    }
  return m;    
}

/*proceduri eliberare memorie vector*/
void free_vector (vector v, int initial, int final)
{
  free((char *)(v + initial));
}

/*proceduri eliberare memorie matrice*/
void free_matrice (matrix m, int initial_linii, int final_linii, int initial_coloane, int final_coloane)
{
    int i;
    for (i=final_linii; i>=initial_linii; i--)
        free ((char *)(m[i] + initial_coloane));
    free((char *)(m + initial_linii));
}

/*functie modul*/
float modul(float x)
{
    float m;
    if (x>0) m=x;
        else if (x==0) m=0;
            else m=-1*x;       
    return m;
}

/*numar complex*/
fcomplex complex(float re, float im)
{
	fcomplex c;
	c.real=re;
	c.imaginar=im;
	return c;
}




