format ELF64 executable 3

include 'include.inc'

;; ------------ SOCKET -----------;;
AF_INET     equ 2
SOCK_STREAM equ 1
IPPROTO_TCP equ 0
; socket can be many types like unix sockets for Inter Process Communication
; but we are choosing the internet domain sockets, i.e ipv4
DOMAIN   equ AF_INET
; after choosing ipv4 domain, we want streaming type connection (tcp), cause its reliable idk!
TYPE     equ SOCK_STREAM
; choosing ipv4 and streaming type socket by defalt protocol is tcp which is defalt 0
PROTOCOL equ IPPROTO_TCP

;; ------------ BIND -----------;;
INADDR_ANY  equ 0
PORT        equ 16415 ; 8000 in big endian, x86_64 is little endian

;---- general socket address(can be internet domain, or unix domain)  -----;
;struct sockaddr {
;    sa_family_t sa_family;
;    char sa_data[4];
;}
;
;---- this is for internet ipv4 domain -----;
; typedef unsigned  short sa_family_t;
; typedef uint16_t  in_port_t
; typedef uint32_t  in_addr_t
; struct  in_addr { in_addr_t s_addr; };
;
;; struct sockaddr_in {
;;     sa_family_t    sin_family;  // 16 bits
;;     in_port_t      sin_port;    // 16 bits
;;     struct in_addr sin_addr;    // 32 bits
;;     uint8_t        sin_zero[8]; // 64 bits
;; }

;; ------------ LISTEN -----------;;
BACKLOG equ 5

;; ------------ ACCEPT -----------;;
; typedef unsigned socklen_t; // 4 bytes

segment readable executable
entry _start
_start:

    print STDOUT, "[INFO] Starting Web Server!", 10

    print STDOUT, "[INFO] Creating socket...", 10
    syscall3 SYS_socket, DOMAIN, TYPE, PROTOCOL
    cmp rax, 0
    jl error
    mov qword [sockfd], rax

    print STDOUT, "[INFO] Binding socket...", 10
    ; fill the server address for server
    mov word  [servaddr.sin_family], AF_INET
    mov word  [servaddr.sin_port],   PORT
    mov dword [servaddr.sin_addr],   INADDR_ANY
    syscall3 SYS_bind, [sockfd], servaddr.sin_family, servaddr_len
    cmp rax, 0
    jl error

    print STDOUT, "[INFO] Listening to socket...", 10
    syscall2 SYS_listen, [sockfd], BACKLOG
    cmp rax, 0
    jl error

    print STDOUT, "[INFO] Accepting request...", 10
next_request:
    syscall3 SYS_accept, [sockfd], clientaddr.sin_family, clientaddr_len ; clientaddr_len will fill by accept, it also return the client fd
    cmp rax, 0
    jl error
    mov qword [connfd], rax
    syscall3 SYS_write, [connfd], response, response_len
    jmp next_request

    print STDOUT, "[INFO] Server closing!", 10
    syscall1 SYS_close, [connfd]
    syscall1 SYS_close, [sockfd]
    syscall1 SYS_exit, EXIT_SUCCESS 

error:
    print STDERR, "[ERROR] exiting the program!", 10
    syscall1 SYS_close, [connfd]
    syscall1 SYS_close, [sockfd]
    syscall1 SYS_exit, EXIT_FAILURE

; db 1 byte
; dw 2 byte
; dd 4 byte
; dq 8 byte
segment readable writeable

;; this will only be written when socket, and accept will success
;; if both fail we might close(-1), but -1 is not a valid fd so no worries
sockfd dq -1 ; server fd
connfd dq -1 ; client fd

struc servaddr_in
{
    .sin_family dw 0
    .sin_port   dw 0
    .sin_addr   dd 0
    .sin_zero   dq 0
}

servaddr servaddr_in
servaddr_len = $ - servaddr.sin_family
clientaddr servaddr_in
clientaddr_len dd 0 ; accept will fill this with client address len

response db "HTTP/1.1 200 OK", 13, 10
         db "Content-Type: text/html; charset=UTF-8", 13, 10
         db "Connection: keep-alive", 13, 10
         db 13, 10
         db "<!DOCTYPE html>", 10
         db "<html>", 10
         db "<head><title>C Web Server</title></head>", 10
         db "<body><h1>Hello from fasm!</h1><p>This is a Http Web Server!</p></body>", 10
         db "</html>", 10
response_len = $ - response
