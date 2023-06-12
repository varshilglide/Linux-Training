#include <unistd.h>

int main() {
    char *str = "Hello, World!\n";
    write(1, str, 14); // 14 is the length of the string
    return 0;
}

