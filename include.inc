SYS_write  equ 1
SYS_close  equ 3
SYS_socket equ 41
SYS_accept equ 43
SYS_bind   equ 49
SYS_listen equ 50
SYS_exit   equ 60

EXIT_SUCCESS equ 0
EXIT_FAILURE equ 1

STDIN  equ 0
STDOUT equ 1
STDERR equ 2

macro syscall1 num, a {
    mov rax, num 
    mov rdi, a
    syscall
}

macro syscall2 num, a, b {
    mov rax, num 
    mov rdi, a
    mov rsi, b
    syscall
}

macro syscall3 num, a, b, c {
    mov rax, num 
    mov rdi, a
    mov rsi, b
    mov rdx, c
    syscall
}

macro print fd, [text] {
    common
        local ..str, ..len, ..skip
        jmp ..skip
        ..str db text
        ..len = $ - ..str
    ..skip:
        syscall3 SYS_write, fd, ..str, ..len
}
