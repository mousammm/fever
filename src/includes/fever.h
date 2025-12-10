/* term.h - Terminal API */
#ifndef FEVER_H
#define FEVER_H

int term_init(void);                    /* Returns master FD or -1 */
int term_read(int fd, char *buf, int len);  /* Read from PTY */
int term_write(int fd, const char *data, int len); /* Write to PTY */

#endif 
