/* x11.h - Minimal X11 window */
#ifndef X11_H
#define X11_H

int x11_init(int width, int height);  /* Initialize window, returns fd */
void x11_draw_char(int x, int y, char c);  /* Draw character at position */
void x11_handle_events(int pty_fd);   /* Handle X11 events, forward to PTY */
void x11_cleanup(void);               /* Cleanup X11 */

#endif
