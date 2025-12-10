/* term.c - Minimal PTY handling */
#include "fever.h"
#include <pty.h>      /* forkpty */
#include <unistd.h>   /* execl, close */
#include <stdio.h>    /* perror */

/* Initialize PTY and start shell
   Returns: master file descriptor on success, -1 on failure */
int term_init(void) {
    int master_fd;
    pid_t pid;
    
    /* STEP 1: Create PTY and fork */
    pid = forkpty(&master_fd, NULL, NULL, NULL);
    
    if (pid < 0) {
        perror("forkpty failed");
        return -1;
    }
    
    if (pid == 0) {
        /* CHILD PROCESS - becomes shell */
        execl("/bin/sh", "sh", NULL);
        
        /* If we get here, execl failed */
        perror("execl failed");
        _exit(1);
    }
    
    /* PARENT PROCESS - return master FD */
    return master_fd;
}

/* Read from PTY master */
int term_read(int fd, char *buf, int len) {
    int n = read(fd, buf, len);
    if (n < 0) {
        perror("read failed");
    }
    return n;
}

/* Write to PTY master (keyboard input) */
int term_write(int fd, const char *data, int len) {
    int n = write(fd, data, len);
    if (n < 0) {
        perror("write failed");
    }
    return n;
}
