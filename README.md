# fever (fasm + server)
A http web server written in fasm(x86_64) assembly.

It follows the basic structure calling the follwing syscalls in order:
```txt
socket -> bind -> listen -> loop(accept)
```

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
