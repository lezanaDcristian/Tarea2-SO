#include "../headers/functions.h"

// Proceso hijo implementado con pipes
/* LISTA */
void childProcessPipe(int *list,int wait_time,int *fd){
	sleep(wait_time);
	printf("¡Hijo terminado! (pid %d):\n",(int)getpid());
	printf("wait_time: %d\n",wait_time);
	printf("Lista original: {");
	int i;
	for(i=0;i<TOTAL_NUMBERS;i++)
		printf("%d,",list[i]);
	printf("\b}\n");
	quickSort(list,TOTAL_NUMBERS-1,0);
	printf("Lista ordenada: {");
	for(i=0;i<TOTAL_NUMBERS;i++)
		printf("%d,",list[i]);
	printf("\b}\n\n");
	close(fd[READ_END]);
	write(fd[WRITE_END],list,sizeof(int)*TOTAL_NUMBERS); 
	close(fd[WRITE_END]);
	return;
}

// Proceso hijo implementado con shared memory
/* LISTA */
void childProcessSharedMemory(int *list,int wait_time){
	sleep(wait_time);
	printf("¡Hijo terminado! (pid %d):\n",(int)getpid());
	printf("wait_time: %d\n",wait_time);
	printf("Lista original: {");
	int i;
	for(i=0;i<TOTAL_NUMBERS;i++)
		printf("%d,",list[i]);
	printf("\b}\n");
	quickSort(list,TOTAL_NUMBERS-1,0);
	printf("Lista ordenada: {");
	for(i=0;i<TOTAL_NUMBERS;i++)
		printf("%d,",list[i]);
	printf("\b}\n");
	/* Creación del segmento de memoria compartida */
	char shm_name[15];
	sprintf(shm_name,"/shm-hijo-%d",(int)getpid());
	int shm_fd=shm_open(shm_name,O_CREAT|O_RDWR,0666);
	/* Configuración del tamaño de la memoria */
	ftruncate(shm_fd,sizeof(int)*TOTAL_NUMBERS);
	/* Mapear la memoria en un puntero local */
	void *ptr=mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_SHARED,shm_fd,0);
	/* Escribir los datos */
	char buffer[20];
	for(i=0;i<TOTAL_NUMBERS;i++){
		sprintf(buffer,"%d,",list[i]);
		sprintf(ptr,"%s",buffer);
		ptr+=sizeof(char)*strlen(buffer);
	}
	printf("\n");
	return;
}

// Función QuickSort (extraida de inet)
/* LISTA */
void quickSort(int lista[], int lim_sup, int lim_inf){
    int izq,der,temporal,pivote;
    izq=lim_inf;
    der=lim_sup;
    pivote=lista[(izq+der)/2];
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
    } while(izq<der);
    if(lim_inf<der){
        quickSort(lista, der, lim_inf);
    }
    if(lim_sup > izq){
        quickSort(lista , lim_sup, izq);
    }
}

// Genera una lista de números enteros random
/* LISTA */
int *randomList(int len,int min,int max){
	if(len<1 || max<min)
		return NULL;
	int *list=calloc((size_t)len,sizeof(int));
	int i;
	for(i=0;i<len;i++)
		list[i]=min+random()%(max-min);
	return list;
}
