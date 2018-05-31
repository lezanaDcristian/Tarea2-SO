#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>

// Definiciones globales

// Modificables
#define TOTAL_NUMBERS      15
#define TOTAL_CHILDS       4
#define MIN_WAIT_TIME      30
#define MAX_WAIT_TIME      60
#define MIN_RANDOM_NUMBER  1
#define MAX_RANDOM_NUMBER  1000

// No modificables
#define READ_END           0
#define WRITE_END          1

// Declaración de funciones

// Proceso hijo implementado con pipes
void childProcessPipe(int*,int,int*);

// Proceso hijo implementado con shared memory
void childProcessSharedMemory(char*,int);

// Función QuickSort (Extraida de inet)
void quickSort(int*,int,int);

// Genera una lista de números enteros random
int *randomList(int,int,int);

#endif
