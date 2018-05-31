#include "../headers/functions.h"

int main(int argc,char **argv){
	srandom(time(NULL));
	/* Declaración de parámetros a utilizar */
	pid_t pid[TOTAL_CHILDS];
	int status[TOTAL_CHILDS];
	int wait_time[TOTAL_CHILDS];
	int *random_list[TOTAL_CHILDS];
	char shm_name[TOTAL_CHILDS][20];
	int shm_fd[TOTAL_CHILDS];
	void *ptr[TOTAL_CHILDS];
	/* Inicialización de parámetros (wait_time, random_list[child], shm_name[child]) */
	int child,i;
	char temp_buffer[10];
	for(child=0;child<TOTAL_CHILDS;child++){
		wait_time[child]=MIN_WAIT_TIME+random()%(MAX_WAIT_TIME-MIN_WAIT_TIME);
		random_list[child]=randomList(TOTAL_NUMBERS,MIN_RANDOM_NUMBER,MAX_RANDOM_NUMBER);
		sprintf(shm_name[child],"/shm-hijo-%d",child);
		/* Creación de memoria compartida para cada hijo */
		shm_fd[child]=shm_open(shm_name[child],O_CREAT|O_RDWR,0666);
		ftruncate(shm_fd[child],5*TOTAL_NUMBERS);
		ptr[child]=mmap(NULL,5*TOTAL_NUMBERS,PROT_READ|PROT_WRITE,MAP_SHARED,shm_fd[child],0);
		/* Escritura de datos de entrada en memoria compartida */
		for(i=0;i<TOTAL_NUMBERS;i++){
			sprintf(temp_buffer,"%d,",random_list[child][i]);
			sprintf(ptr[child],"%s",temp_buffer);
			ptr[child]+=sizeof(char)*strlen(temp_buffer);
		}
	}
	/* Generación de procesos hijos */
	for(child=0;child<TOTAL_CHILDS;child++){
		pid[child]=fork();
		if(pid[child]<0){//se produce un error
			fprintf(stderr,"Fork Falla\n");
			return 1;
		}
		if(pid[child]==0){//proceso hijo child-ésimo
			childProcessSharedMemory(shm_name[child],wait_time[child]);
			return 0;
		}
	}
	/* Luego de generar todos los hijos, hay que esperar a cada uno */
	printf("¡Hijos generados con éxito! (%d en total)\n",TOTAL_CHILDS);
	printf("Esperando que todos terminen...\n\n");
	for(child=0;child<TOTAL_CHILDS;child++)
		waitpid(pid[child],&status[child],0);
	/* Finalmente se lee y muestra por pantalla el resultado */
	printf("Lectura del Padre:\n");
	for(child=0;child<TOTAL_CHILDS;child++){
		sprintf(shm_name[child],"/shm-hijo-%d",(int)pid[child]);
		shm_fd[child]=shm_open(shm_name[child],O_RDONLY,0666);
		ptr[child]=mmap(NULL,5*TOTAL_NUMBERS,PROT_READ,MAP_SHARED,shm_fd[child],0);
		printf("Hijo %d (pid %d): {",child+1,(int)pid[child]);
		printf("%s",(char*)ptr[child]);
		printf("\b}\n");
		shm_unlink(shm_name[child]);
	}
	printf("\n");
	return 0;
}
