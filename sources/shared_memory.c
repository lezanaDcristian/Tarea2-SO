#include "../headers/functions.h"

int main(int argc,char **argv){
	srandom(time(NULL));
	/* Declaración de parámetros a utilizar */
	pid_t pid[TOTAL_CHILDS];
	int status[TOTAL_CHILDS];
	int wait_time[TOTAL_CHILDS];
	int *random_list[TOTAL_CHILDS];
	/* Inicialización de parámetros (wait_time, random_list[child]) */
	int child;
	for(child=0;child<TOTAL_CHILDS;child++){
		wait_time[child]=MIN_WAIT_TIME+random()%(MAX_WAIT_TIME-MIN_WAIT_TIME);
		random_list[child]=randomList(TOTAL_NUMBERS,MIN_RANDOM_NUMBER,MAX_RANDOM_NUMBER);
	}
	/* Generación de procesos hijos */
	for(child=0;child<TOTAL_CHILDS;child++){
		pid[child]=fork();
		if(pid[child]<0){//se produce un error
			fprintf(stderr,"Fork Falla\n");
			return 1;
		}
		if(pid[child]==0){//proceso hijo child-ésimo
			childProcessSharedMemory(random_list[child],wait_time[child]);
			return 0;
		}
	}
	/* Luego de generar todos los hijos, hay que esperar a cada uno */
	printf("¡Hijos generados con éxito! (%d en total)\n",TOTAL_CHILDS);
	printf("Esperando que todos terminen...\n\n");
	for(child=0;child<TOTAL_CHILDS;child++)
		waitpid(pid[child],&status[child],0);
	/* Finalmente se lee y muestra por pantalla el resultado */
	int shm_fd,i;
	void *ptr;
	char shm_name[15];
	printf("Lectura del Padre:\n");
	for(child=0;child<TOTAL_CHILDS;child++){
		sprintf(shm_name,"/shm-hijo-%d",(int)pid[child]);
		shm_fd=shm_open(shm_name,O_RDONLY,0666);
		ptr=mmap(NULL,4096,PROT_READ,MAP_SHARED,shm_fd,0);
		printf("Hijo %d (pid %d): {",child+1,(int)pid[child]);
		printf("%s",(char*)ptr);
		printf("\b}\n");
		shm_unlink(shm_name);
	}
	printf("\n");
	return 0;
}
