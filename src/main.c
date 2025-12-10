/* main.c - Test the PTY */
#include "fever.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <signal.h> // a2
#include "x11.h"    // a3

// a3
#define COLS 80
#define ROWS 24

int main() {
    /* STEP 1: Initialize PTY */
    /* int fd = term_init(); */
    int pty_fd = term_init();
    printf("%d\n",pty_fd); // a3
    if (pty_fd < 0){ // a3
        fprintf(stderr, "Failed to initialize PTY\n"); // a3
        return 1;
    }

    /* Initialize X11 window */ // a3
    int x11_fd = x11_init(COLS * 8, ROWS * 16);
    if (x11_fd < 0) {
        term_cleanup(pty_fd);
        return 1;
    }

    printf("Terminal ready. Close window to exit.\n"); // a3
    
    // a3
    /* printf("PTY created. FD=%d\n", fd); */
    /* printf("Shell ready. Commands won't echo here.\n"); // a2 */
    /* printf("Type 'exit' or press Ctrl+D to quit.\n"); // a2 */
    
    /* STEP 2: Simple I/O loop */
    fd_set fds;
    char buf[256];
    char screen[ROWS][COLS] = {0};  /* Simple screen buffer */ // a3
    int cursor_x = 0, cursor_y = 0; // a3
    /* int running = 1; // a2 */
    
    while (1) { // a2, a3
        FD_ZERO(&fds);
        /* FD_SET(STDIN_FILENO, &fds);  /1* Keyboard *1/ */
        /* FD_SET(fd, &fds);            /1* Shell output *1/ */
        FD_SET(pty_fd, &fds);  /* shell output */ // a3
        FD_SET(x11_fd, &fds);  /* x11 events */   // a3
        
        /* Wait for activity */
        /* select(fd+1, &fds, NULL, NULL, NULL); */
        int max_fd = (pty_fd > x11_fd) ? pty_fd : x11_fd; // a3
        select(max_fd + 1, &fds, NULL, NULL, NULL); // a3
        
        /* Keyboard -> Shell */
        if (FD_ISSET(pty_fd, &fds)) { // a3
            /* int n = read(STDIN_FILENO, buf, sizeof(buf)); */
            int n = term_read(pty_fd, buf, sizeof(buf));
            /* if (n > 0) term_write(fd, buf, n); */ // a2
            if(n > 0) { //a2
                
                /* Simple screen update (we'll improve later) */// a3
                for (int i = 0; i < n; i++) {
                    if (buf[i] == '\n') {
                        cursor_x = 0;
                        cursor_y++;
                    } else if (buf[i] == '\r') {
                        cursor_x = 0;
                    } else {
                        screen[cursor_y][cursor_x] = buf[i];
                        cursor_x++;
                        if (cursor_x >= COLS) {
                            cursor_x = 0;
                            cursor_y++;
                        }
                    }

                    /* Simple scrolling */
                    if (cursor_y >= ROWS) {
                        cursor_y = ROWS - 1;
                        /* Shift lines up (basic scroll) */
                        for (int y = 0; y < ROWS - 1; y++) {
                            for (int x = 0; x < COLS; x++) {
                                screen[y][x] = screen[y + 1][x];
                            }
                        }
                        /* Clear bottom line */
                        for (int x = 0; x < COLS; x++) {
                            screen[ROWS - 1][x] = ' ';
                        }
                    }

                    /* Draw character in X11 */
                    x11_draw_char(cursor_x, cursor_y, buf[i]);
                } // a3 for loop 
            } // a3 if end
        } // a3 if 

        /* X11 events (keyboard input) */ // a3
        if (FD_ISSET(x11_fd, &fds)) {
            x11_handle_events(pty_fd);
        }
    } //a3 while end
 

                 //a3
                 /* /1* Check for Ctrl+D (EOF) *1/ */
                /* if (n == 1 && buf[0] == 4) { */
                 /*    term_write(fd, "exit\n", 5); */
                 /*    running = 0; */
                /* } else { */
                 /*    term_write(fd, buf, n); */
                /* } */               
            /* }else if (n == 0) { */
                /* running = 0;  /1* EOF *1/ */
            /* } // a2 */
        /* } */
        
        /* /1* Shell -> Screen *1/ */
        /* if (FD_ISSET(fd, &fds)) { */
            /* int n = term_read(fd, buf, sizeof(buf)); */
            /* /1* if (n > 0) write(STDOUT_FILENO, buf, n); *1/ // a2 */

            /* if(n > 0) { // a2 */
                /* write(STDOUT_FILENO, buf, n); */
            /* } else if (n == 0) { */
                /* running = 0; // shell closed */
            /* } // a2 */

        /* } */
    /* } */
    
    /* close(fd); */ // a2
    x11_cleanup(); //a3
    term_cleanup(pty_fd);
    /* term_cleanup(fd); */
    printf("\n fever closed \n");

    return 0;
}
