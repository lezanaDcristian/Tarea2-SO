#include "../headers/functions.h"

int main(int argc,char **argv){
	srand(time(NULL));
	pid_t pid1,pid2,pid3,pid4;
	int status1,status2,status3,status4;
	int fd1[2],fd2[2],fd3[2],fd4[2];
	int wait_time1,wait_time2,wait_time3,wait_time4;
	int *list1,*list2,*list3,*list4;
	pipe(fd1);
	pipe(fd2);
	pipe(fd3);
	pipe(fd4);
	wait_time1=rand()%30+30;
	wait_time2=rand()%30+30;
	wait_time3=rand()%30+30;
	wait_time4=rand()%30+30;
	list1=randomList(TOTAL_NUMBERS,1,1000);
	list2=randomList(TOTAL_NUMBERS,1,1000);
	list3=randomList(TOTAL_NUMBERS,1,1000);
	list4=randomList(TOTAL_NUMBERS,1,1000);
	pid1=fork();
	if(pid1<0){//se produce un error
		fprintf(stderr,"Fork Falla\n");
		return 1;
	}
	else if(pid1==0){//proceso hijo 1
		childProcessPipes(list1,fd1,wait_time1);
	}
	else{//proceso padre
		pid2=fork();
		if(pid2<0){
			fprintf(stderr,"Fork Falla\n");
			return 1;
		}
		else if(pid2==0){//proceso hijo 2
			childProcessPipes(list2,fd2,wait_time2);
		}
		else{//proceso padre
			pid3=fork();
			if(pid3<0){
				fprintf(stderr,"Fork Falla\n");
				return 1;
			}
			else if(pid3==0){//proceso hijo 3
				childProcessPipes(list3,fd3,wait_time3);
			}
			else{//proceso padre
				pid4=fork();
				if(pid4<0){
					fprintf(stderr,"Fork Falla\n");
					return 1;
				}
				else if(pid4==0){//proceso hijo 4
					childProcessPipes(list4,fd4,wait_time4);
				}
				else {//proceso padre
					waitpid(pid1,&status1,0);
					waitpid(pid2,&status2,0);
					waitpid(pid3,&status3,0);
					waitpid(pid4,&status4,0);
					close(fd1[WRITE_END]);
					close(fd2[WRITE_END]);
					close(fd3[WRITE_END]);
					close(fd4[WRITE_END]);
					read(fd1[READ_END],list1,sizeof(int)*TOTAL_NUMBERS);
					read(fd2[READ_END],list2,sizeof(int)*TOTAL_NUMBERS);
					read(fd3[READ_END],list3,sizeof(int)*TOTAL_NUMBERS);
					read(fd4[READ_END],list4,sizeof(int)*TOTAL_NUMBERS);
					int i;
					printf("Padre:\n");
					printf("Hijo 1 (pid %d): {",(int)pid1);
					for(i=0;i<TOTAL_NUMBERS;i++)
						printf("%d,",list1[i]);
					printf("\b}\n");
					printf("Hijo 2 (pid %d): {",(int)pid2);
					for(i=0;i<TOTAL_NUMBERS;i++)
						printf("%d,",list2[i]);
					printf("\b}\n");
					printf("Hijo 3 (pid %d): {",(int)pid3);
					for(i=0;i<TOTAL_NUMBERS;i++)
						printf("%d,",list3[i]);
					printf("\b}\n");
					printf("Hijo 4 (pid %d): {",(int)pid4);
					for(i=0;i<TOTAL_NUMBERS;i++)
						printf("%d,",list4[i]);
					printf("\b}\n");
				}
			}
		}
	}
	return 0;
}
