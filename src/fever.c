/* term.c - Minimal PTY handling */
#include "fever.h"
#include <pty.h>      /* forkpty */
#include <unistd.h>   /* execl, close */
#include <stdio.h>    /* perror */
#include <termios.h> // a2

/* Save original terminal settings */
static struct termios original_termios; // a2

/* Set terminal to raw mode */
static void enable_raw_mode(int fd) {   // a2
    struct termios t;
    tcgetattr(fd, &original_termios);
    tcgetattr(fd, &t);
    
    /* Disable echo, line buffering, special chars */
    t.c_lflag &= ~(ECHO | ICANON | ISIG);
    t.c_iflag &= ~(IXON | ICRNL);
    t.c_oflag &= ~(OPOST);
    
    tcsetattr(fd, TCSANOW, &t);
}

/* Restore original terminal mode */
static void disable_raw_mode(int fd) {  // a2
    tcsetattr(fd, TCSANOW, &original_termios);
}

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

    /* PARENT - set our terminal to raw mode */
    enable_raw_mode(STDIN_FILENO);   // a2
    
    /* PARENT PROCESS - return master FD */
    return master_fd;
}

/* Cleanup - restore terminal */ // a2
void term_cleanup(int fd) {
    disable_raw_mode(STDIN_FILENO);
    close(fd);
}

/* Read from PTY master */
int term_read(int fd, char *buf, int len) {
    /* int n = read(fd, buf, len); */
    /* if (n < 0) { */
    /*     perror("read failed"); */
    /* } */
    /* return n; */
    return read(fd, buf, len); //a2
}

/* Write to PTY master (keyboard input) */
int term_write(int fd, const char *data, int len) {
    /* int n = write(fd, data, len); */
    /* if (n < 0) { */
    /*     perror("write failed"); */
    /* } */
    /* return n; */
    return write(fd, data, len);  //a2
}
