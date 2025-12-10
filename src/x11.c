// X11 window & drawing
/* x11.c - Minimal X11 window */
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <unistd.h>
#include "x11.h"

static Display *dpy = NULL;
static Window win;
static GC gc;
static int char_width = 8, char_height = 16;

/* Initialize X11 window */
int x11_init(int width, int height) {
    /* Open display */
    dpy = XOpenDisplay(NULL);
    if (!dpy) {
        fprintf(stderr, "Cannot open display\n");
        return -1;
    }
    
    /* Create window */
    int screen = DefaultScreen(dpy);
    win = XCreateSimpleWindow(dpy, RootWindow(dpy, screen),
                             0, 0, width, height, 1,
                             BlackPixel(dpy, screen),
                             WhitePixel(dpy, screen));
    
    /* Set window title */
    XStoreName(dpy, win, "Fever TTY");
    
    /* Select input events */
    XSelectInput(dpy, win, ExposureMask | KeyPressMask);
    
    /* Create graphics context */
    gc = XCreateGC(dpy, win, 0, NULL);
    XSetForeground(dpy, gc, BlackPixel(dpy, screen));
    
    /* Map window (make it visible) */
    XMapWindow(dpy, win);
    XFlush(dpy);
    
    /* Return X11 connection file descriptor for select() */
    return ConnectionNumber(dpy);
}

/* Draw character at position */
void x11_draw_char(int x, int y, char c) {
    if (!dpy) return;
    
    char str[2] = {c, 0};
    XDrawString(dpy, win, gc,
                x * char_width, y * char_height + char_height - 4,
                str, 1);
}

/* Handle X11 events */
void x11_handle_events(int pty_fd) {
    if (!dpy) return;
    
    while (XPending(dpy)) {
        XEvent ev;
        XNextEvent(dpy, &ev);
        
        switch (ev.type) {
        case Expose:
            /* Window needs redraw - we'll implement later */
            break;
            
        case KeyPress:
            /* Keyboard input */
            char buf[32];
            int len = XLookupString(&ev.xkey, buf, sizeof(buf), NULL, NULL);
            if (len > 0 && pty_fd >= 0) {
                write(pty_fd, buf, len);
            }
            break;
        }
    }
}

/* Cleanup */
void x11_cleanup(void) {
    if (dpy) {
        XCloseDisplay(dpy);
        dpy = NULL;
    }
}
