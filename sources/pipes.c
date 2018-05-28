#include "../headers/functions.h"

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
		//ProcesoHijo("Datos1.txt","Output1.txt");
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
			//ProcesoHijo("Datos2.txt","Output2.txt");
		}
		else { /* proceso padre */
		
			pid3=fork();
		
			if(pid3<0){
				fprintf(stderr, "Fork Falla\n");
				return 1;
			}
		
			else if (pid3 == 0) { /* proceso hijo */
				srand(time(NULL)+150);//Setear la semilla del random
				//ProcesoHijo("Datos3.txt","Output3.txt");
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
					//ProcesoHijo("Datos4.txt","Output4.txt");
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

