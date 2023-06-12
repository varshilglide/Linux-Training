#include <stdio.h>
#include <unistd.h>		// header for pipe systemcall
#include <string.h>

int main(){

	int pipeFd[2] = {0};
	pid_t cid;

	printf("Creating pipe. . .\n");
	if( pipe(pipeFd) < 0 ){					// opening pipe, pipeFd[0]: read end of pipe, pipeFd[1]: write end of pipe
		perror("error in creating pipe");
		return -1;
	}

	cid = fork();	// systemcall used to create a new process by duplicating the calling process

	if(cid){
		// this is parent process
		char *str1 = "Hello Child. . .!";
		printf("parents PID: %d\n", getpid());
		printf("MSG to child: %s\n", str1);
		if( write(pipeFd[1], str1, strlen(str1)) < 0 ) {
			perror("error in write");
			return -1;
		}
	}
	else{
		// this is child process
		printf("\nchild PID: %d, PPID: %d\n", cid, getppid());
		char str2[25] = {0};
		if( read(pipeFd[0], str2, sizeof(str2)) < 0 ){
			perror("error in read");
			return -1;
		}
		printf("MSG from parent: %s\n",str2);
	}


	
	close(pipeFd[0]);
	close(pipeFd[1]);

	return 0;
}
