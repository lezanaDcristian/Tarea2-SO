#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definiciones globales
#define TOTAL_NUMBERS  15
#define READ_END       0
#define WRITE_END      1

// Declaración de funciones

// Proceso hijo implementado con pipes
void childProcessPipes(int*,int*,int);

// Proceso hijo implementado con shared memory
void childProcessSharedMemory(int*);

// Función QuickSort (Extraida de inet)
void quickSort(int *, int , int);

// Genera una lista de números enteros random
int *randomList(int,int,int);

#endif
