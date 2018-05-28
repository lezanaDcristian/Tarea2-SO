#include "../headers/functions.h"

int main(int argc,char **argv){
	srandom(time(NULL));
	/* Declaración de par+ametros a utilizar */
	pid_t pid[TOTAL_CHILDS];
	int status[TOTAL_CHILDS];
	int fd[TOTAL_CHILDS][2];
	int wait_time[TOTAL_CHILDS];
	int *random_list[TOTAL_CHILDS];
	int child;
	/* Inicialización de parámetros (pipes, wait_time, random_list[child])*/
	for(child=0;child<TOTAL_CHILDS;child++){
		if(pipe(fd[child])==-1){
			fprintf(stderr,"Pipe failed\n");
			return 1;
		}
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
			childProcessPipe(random_list[child],fd[child],wait_time[child]);
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
	int i;
	int list_buffer[TOTAL_CHILDS][TOTAL_NUMBERS];
	for(child=0;child<TOTAL_CHILDS;child++){
		close(fd[child][WRITE_END]);
		read(fd[child][READ_END],list_buffer[child],sizeof(int)*TOTAL_NUMBERS);
		close(fd[child][READ_END]);
		printf("Hijo %d (pid %d): {",child,(int)pid[child]);
		for(i=0;i<TOTAL_NUMBERS;i++)
			printf("%d,",list_buffer[child][i]);
		printf("\b}\n");
	}
	printf("\n");
	return 0;
}
