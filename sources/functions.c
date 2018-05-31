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
void childProcessSharedMemory(char *shm_name,int wait_time){
	sleep(wait_time);
	/* Leyendo datos desde la memoria compartida por el padre */
	int shm_fd=shm_open(shm_name,O_RDWR,0666);
	ftruncate(shm_fd,5*TOTAL_NUMBERS);
	void *ptr=mmap(NULL,5*TOTAL_NUMBERS,PROT_READ|PROT_WRITE,MAP_SHARED,shm_fd,0);
	char *temp_string=(char*)ptr;
	char *temp_number=strtok(temp_string,",");
	int temp_list[TOTAL_NUMBERS];
	int i=0;
	while(temp_number!=NULL){
		temp_list[i]=atoi(temp_number);
		temp_number=strtok(NULL,",");
		i++;
	}
	/* Hijo muestra información relevante por pantalla */
	printf("¡Hijo terminado! (pid %d):\n",(int)getpid());
	printf("wait_time: %d\n",wait_time);
	printf("Lista original: {");
	for(i=0;i<TOTAL_NUMBERS;i++)
		printf("%d,",temp_list[i]);
	printf("\b}\n");
	quickSort(temp_list,TOTAL_NUMBERS-1,0);
	printf("Lista ordenada: {");
	for(i=0;i<TOTAL_NUMBERS;i++)
		printf("%d,",temp_list[i]);
	printf("\b}\n");
	shm_unlink(shm_name);
	/* Creación de un nuevo segmento de memoria compartida */
	char new_shm_name[20];
	sprintf(new_shm_name,"shm-hijo-%d",(int)getpid());
	shm_fd=shm_open(new_shm_name,O_CREAT|O_RDWR,0666);
	/* Configuración del tamaño de la memoria */
	ftruncate(shm_fd,5*TOTAL_NUMBERS);
	/* Mapear la memoria en un puntero local */
	ptr=mmap(NULL,5*TOTAL_NUMBERS,PROT_READ|PROT_WRITE,MAP_SHARED,shm_fd,0);
	/* Escribir los datos */
	char buffer[20];
	for(i=0;i<TOTAL_NUMBERS;i++){
		sprintf(buffer,"%d,",temp_list[i]);
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
