#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Global definitions:
#define TAMANO_LISTA 20  

// Function declarations:

// Función adquiere los datos dentro del archivo de texto.
void GenerarLista(char *, int *);

// Función toma una lista y la escribe en un archivo de texto.
void EscribirLista(int *, char *);

// Función QuickSort (Extraida de inet)
void QuickSort(int *, int , int);

// Proceso que realiza el hijo
void ProcesoHijo(char *,char *);

// Genera una lista de números enteros random
int *randomList(int,int,int);

#endif
