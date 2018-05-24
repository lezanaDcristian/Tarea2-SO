#include "./functions.h"

// Función adquiere los datos dentro del archivo de texto.
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

// Función toma una lista y la escribe en un archivo de texto.
void EscribirLista(int lista[], char NombreDeArchivo[]){ //NombreDeArchivo terminar en .txt
    FILE *archivo=NULL;
    char temporal[5];
    archivo = fopen(NombreDeArchivo, "w");// Abrir archivo vacio en modo escritura
    for(int i=0; i<TAMANO_LISTA; i++)
        fprintf(archivo,"%d\n",lista[i]);// Escritura de lista en el archivo
    fclose(archivo);// Cerrar archivo
    return;
}

// Función QuickSort (Extraida de inet)
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

// Proceso que realiza el hijo
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

// Genera una lista de números enteros random
int *randomList(int len,int min,int max){
	if(len<1 || max<min)
		return NULL;
	int *list=calloc((size_t)len,sizeof(int));
	int i;
	for(i=0;i<len;i++)
		list[i]=min+random()%(max-min);
	return list;
}




