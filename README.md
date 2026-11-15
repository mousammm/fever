# fever (fasm + server)
A http web server written in fasm(x86_64) assembly.

## P1 HTTP Server with CRUD Operations (No Database, Filesystem Only)

A single-threaded HTTP server that handles one client at a time and uses
the filesystem as its storage layer.

- [x] started
- [x] Basic server structure, can listen for and accept client connections synchronously
- [ ] Parse incoming HTTP requests
- [ ] Dispatch on method and route path to different handlers (GET, PUT, PATCH, DELETE)

## P2 Web Server in C with Multithreading and SQLite3

A multithreaded web server written in C, using SQLite3 as the storage backend.

- [x] Not started

**Building**
> [NOTE]
> x86_64 machine with Linux, and [fasm-1.73.35.tgz](https://flatassembler.net/fasm-1.73.35.tgz) in $PATH.
```
$ fasm main.asm
$ ./main
```
- visit : [http://localhost:8000](http://localhost:8000)

**Refrences**
- [tsoding](https://youtu.be/b-q4QBy52AA?si=c8JIx-4ZqbVxT7GA)
