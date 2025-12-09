// File: step1.c
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int main() {
    struct termios old, new;
    tcgetattr(0, &old);
    new = old;
    new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &new);
    
    char c;
    while (read(0, &c, 1) == 1) {
        printf("Got: %d '%c'\n", c, c);
    }
    
    tcsetattr(0, TCSANOW, &old);
    return 0;
}
