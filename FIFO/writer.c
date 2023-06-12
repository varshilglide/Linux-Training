#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(){
	
	int fifoFd = -1;
	char *fifoName = "/tmp/myfifo";

	printf("Creating fifo. . .\n");
	if( mkfifo(fifoName, 0777) < 0 ){
		perror("error in creating fifo");
		return -1;
	}

	printf("Opening %s to write. . .\n", fifoName);
	fifoFd = open(fifoName, O_WRONLY);
	if( fifoFd < 0 ){
		perror("error in opening fifo");
		return -1;
	}

	printf("Writing data on fifo. . .\n");
	char *msg = "Hello process-2";
	if( write(fifoFd, msg, strlen(msg)+1) < 0){
		perror("error in write");
		return -1;
	}
	sleep(1);
	msg = "Good bye process-2";
	if( write(fifoFd, msg, strlen(msg)+1) < 0){
                perror("error in write");
                return -1;
        }

	close(fifoFd);
	fifoFd = -1;

	return 0;
}
