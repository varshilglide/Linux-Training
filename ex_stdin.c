#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];
    ssize_t nread;
    
    while ((nread = read(0, buffer, BUFFER_SIZE)) > 0) {
        write(1, buffer, nread);
    }
    
    return 0;
}

