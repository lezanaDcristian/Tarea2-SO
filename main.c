#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TAMANO_LISTA 20  

//Declaracion de funciones
void GenerarLista(char *, int *);
void EscribirLista(int *, char *);
void QuickSort(int *, int , int);
void ProcesoHijo(char *,char *);

//Main
int main(){
	pid_t pid1,pid2,pid3,pid4;
	/* bifurca a un proceso hijo  */
	pid1 = fork();
	if (pid1 < 0) { /* se produce un error */
		fprintf(stderr, "Fork Falla\n");
		return 1;
	}
	else if (pid1 == 0) { /* proceso hijo */
		srand(time(NULL)+50);//Setear la semilla del random
		ProcesoHijo("Datos1.txt","Output1.txt");
	}
	else { /* proceso padre */
		/* el padre espera que el proceso hijo se complete */
		
		pid2=fork();
		
		if(pid2<0){
			fprintf(stderr, "Fork Falla\n");
			return 1;
		}
		
		else if (pid2 == 0) { /* proceso hijo */
			srand(time(NULL)+100);//Setear la semilla del random
			ProcesoHijo("Datos2.txt","Output2.txt");
		}
		else { /* proceso padre */
		
			pid3=fork();
		
			if(pid3<0){
				fprintf(stderr, "Fork Falla\n");
				return 1;
			}
		
			else if (pid3 == 0) { /* proceso hijo */
				srand(time(NULL)+150);//Setear la semilla del random
				ProcesoHijo("Datos3.txt","Output3.txt");
			}
			else { /* proceso padre */
				/* el padre espera que el proceso hijo se complete */
		
				pid4=fork();
		
				if(pid4<0){
					fprintf(stderr, "Fork Falla\n");
					return 1;
				}
		
				else if (pid4 == 0) { /* proceso hijo */
					srand(time(NULL)+200);//Setear la semilla del random
					ProcesoHijo("Datos4.txt","Output4.txt");
				}
				else { /* proceso padre */
					/* el padre espera que el proceso hijo se complete */
		
					wait(NULL);
					wait(NULL);
					wait(NULL);
					wait(NULL);
		
				}
		
			}
		
		}
	}
    return 0;   
}

//Función adquiere los datos dentro del archivo de texto.
void GenerarLista(char NombreArchivo[], int lista[]){
    FILE *archivo;
    int contador = 0;
    char caracteres[5];
    archivo = fopen(NombreArchivo, "r"); //Nombre de archivo terminar en .txt. Se abre en modo lectura
    if(archivo == NULL){
        exit(1);
    } 
    else{
        while(feof(archivo) == 0){// Almacena caracteres en la lista ingresada
            fgets(caracteres,5,archivo);
            lista[contador] = atoi(caracteres);
            contador = contador + 1;
        }
    }
    fclose(archivo);// Cierra archivo
    return;
}

//Función toma una lista y la escribe en un archivo de texto.
void EscribirLista(int lista[], char NombreDeArchivo[]){ //NombreDeArchivo terminar en .txt
    FILE *archivo=NULL;
    char temporal[5];
    archivo = fopen(NombreDeArchivo, "w");// Abrir archivo vacio en modo escritura
    for(int i=0; i<TAMANO_LISTA; i++)
        fprintf(archivo,"%d\n",lista[i]);// Escritura de lista en el archivo
    fclose(archivo);// Cerrar archivo
    return;
}

//Función QuickSort (Extraida de inet)
void QuickSort(int lista[], int lim_sup, int lim_inf){
    int izq,der,temporal,pivote;
    izq = lim_inf;
    der = lim_sup;
    pivote = lista[(izq+der)/2];
    do{
        while(lista[izq]<pivote && izq<lim_sup){
            izq++;
        }
        while(lista[der]>pivote && der> lim_inf){
            der--;
        }
        if(izq <= der){
            temporal = lista[izq];
            lista[izq] = lista[der];
            lista[der] = temporal;
            izq++;
            der--;
        }
    }while(izq < der);
    if(lim_inf<der){
        QuickSort(lista, der, lim_inf);
    }
    if(lim_sup > izq){
        QuickSort(lista , lim_sup, izq);
    }
}

//Proceso que realiza el hijo

void ProcesoHijo(char NombreArchivo[],char SalidaArchivo[]){
	int rd=random()%30+30;// Tiempo de espera entre 30 y 60 segundos
	int lista[TAMANO_LISTA]={[0 ... TAMANO_LISTA-1]=0};

	printf("Proceso hijo:PID mio: %d,  Tiempo de espera: %d, PID padre: %d\n",getpid(),rd, getppid());
	sleep(rd);// Espera de proceso
	GenerarLista(NombreArchivo,lista);
	QuickSort(lista,TAMANO_LISTA,0);
	EscribirLista(lista,SalidaArchivo);	
	return;
}
