#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(){
	
	int fifoFd = -1;
	char *fifoName = "/tmp/myfifo";

	printf("Opening %s to read. . .\n", fifoName);
	fifoFd = open(fifoName, O_RDONLY);
	if( fifoFd < 0 ){
		perror("error in opening fifo");
		return -1;
	}

	printf("Reading data from fifo. . .\n");
	char msg[25] = {0};
	if( read(fifoFd, msg, sizeof(msg)) < 0){
		perror("error in read");
		return -1;
	}
	printf("MSG: %s\n", msg);

	memset(msg, 0, sizeof(msg));	
	if( read(fifoFd, msg, sizeof(msg)) < 0){
                perror("error in read");
                return -1;
        }

	printf("MSG: %s\n", msg);
	
	close(fifoFd);
	fifoFd = -1;
	unlink(fifoName);

	return 0;
}
