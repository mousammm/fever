/* main.c - Test the PTY */
#include "fever.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>

int main() {
    /* STEP 1: Initialize PTY */
    int fd = term_init();
    if (fd < 0) return 1;
    
    printf("PTY created. FD=%d\n", fd);
    printf("Type 'exit' to quit\n\n");
    
    /* STEP 2: Simple I/O loop */
    fd_set fds;
    char buf[256];
    
    while (1) {
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);  /* Keyboard */
        FD_SET(fd, &fds);            /* Shell output */
        
        /* Wait for activity */
        select(fd+1, &fds, NULL, NULL, NULL);
        
        /* Keyboard -> Shell */
        if (FD_ISSET(STDIN_FILENO, &fds)) {
            int n = read(STDIN_FILENO, buf, sizeof(buf));
            if (n > 0) term_write(fd, buf, n);
        }
        
        /* Shell -> Screen */
        if (FD_ISSET(fd, &fds)) {
            int n = term_read(fd, buf, sizeof(buf));
            if (n > 0) write(STDOUT_FILENO, buf, n);
        }
    }
    
    close(fd);
    return 0;
}
