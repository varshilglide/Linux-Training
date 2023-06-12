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

    printf("Opening message queue. . .\n");
    q_des = mq_open(q_name, O_RDONLY, 0644, &q_attr);
    if( q_des < 0){
        perror("error in creation of message queue");
        return -1;
    }

    char msg[msg_size];
    printf("Receiving data on message queue. . .\n");
    if( mq_receive(q_des, msg, sizeof(msg), 0) == -1 ){
        perror("error in receiving data over mq");
        return -1;
    }
    printf("MSG from sender: %s\n", msg);

    return 0;
}
