#include <stdio.h>
#include <mqueue.h>
#include <sys/stat.h>   // for mode constants
#include <fcntl.h>      // for O_* constants
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

const char *q_name = "/mqTest";
const uint8_t msg_size = 128;

int main(){
    struct mq_attr q_attr;
    mqd_t q_des;

    q_attr.mq_maxmsg = 10;
    q_attr.mq_msgsize = msg_size;
    q_attr.mq_curmsgs = 0;

    if( mq_unlink(q_name) == 0 ){
        printf("removed existing mq\n");
    }

    printf("Creating message queue. . .\n");
    q_des = mq_open(q_name, O_CREAT | O_WRONLY , 0644, &q_attr);
    if( q_des < 0){
        perror("error in creation of message queue");
        return -1;
    }

    char *msg = "Hello received end. . .";
    printf("Writing data: \"%s\" on message queue. . .\n", msg);
    if( mq_send(q_des, msg, strlen(msg)+1, 0) < 0 ){
        perror("error in sending data over mq");
        return -1;
    }

    return 0;
}
