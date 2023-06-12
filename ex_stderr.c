#include <unistd.h>

int main() {
    char *str = "Error: something went wrong!\n";
    write(2, str, 29); // 29 is the length of the string
    return 0;
}

