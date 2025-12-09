# Fever - A Minimal Terminal Emulator

## Overview
Fever is a simple terminal emulator written in C, created to understand how terminals work internally and gain hands-on experience with low-level C programming. The codebase is intentionally minimal and easy to understand, serving as both a learning tool and a foundation for building your own terminal emulator.

## Purpose
This project aims to:
- Demystify how terminal emulators work under the hood
- Provide practical experience with C programming
- Create a clean, understandable codebase for learning

## Current Features
- [ ] Basic terminal emulation
- [ ] Raw input mode handling
- [ ] VT100/xterm escape sequence parsing
- [ ] Character display
- [ ] Cursor movement
- [ ] Basic text editing (backspace, enter)
- [ ] Simple command execution
- [ ] Scrollback buffer

## Building
```bash
make
```

## Usage
```bash
make run
```

## How Terminals Work (Simplified)
1. **Raw Mode**: Terminal disables canonical mode to read input character-by-character
2. **Escape Sequences**: Special character sequences control cursor, colors, and formatting
3. **Pseudo-Terminal (PTY)**: Creates master/slave pair for program I/O
4. **Input Processing**: Translates keystrokes and sends to child process
5. **Output Rendering**: Displays text and interprets control characters

## Project Structure
```
TODO
```

## Learning Objectives
- Terminal I/O and PTY handling
- Escape sequence parsing
- Raw vs cooked terminal modes
- Process management (fork/exec)
- Signal handling
- Buffer management

## TODO Features List

### Phase 1: Core Functionality
- [ ] Set up raw terminal mode
- [ ] Implement basic input reading loop
- [ ] Display typed characters
- [ ] Handle backspace and enter keys
- [ ] Create PTY master/slave pair
- [ ] Fork and exec shell process
- [ ] Forward input to child process
- [ ] Display output from child process

### Phase 2: Terminal Features
- [ ] Parse VT100 escape sequences
- [ ] Implement cursor movement (arrows)
- [ ] Add scrollback buffer
- [ ] Handle window resize signals
- [ ] Basic text selection (copy/paste)
- [ ] Support for function keys
- [ ] Tab completion framework

### Phase 3: Advanced Features
- [ ] Multiple tabs/windows
- [ ] Color support (16 colors)
- [ ] True color support (RGB)
- [ ] Customizable key bindings
- [ ] Search in scrollback
- [ ] Unicode/UTF-8 support
- [ ] Split panes
- [ ] Session saving/restoring

### Phase 4: Polish & Optimization
- [ ] Efficient screen redraw
- [ ] Double buffering
- [ ] Configuration file support
- [ ] Themes and color schemes
- [ ] Performance optimizations
- [ ] Memory leak fixes
- [ ] Comprehensive error handling

## Getting Started Guide
1. Start by implementing raw mode (disable echo, canonical mode)
2. Create a basic read/display loop
3. Add PTY functionality to run actual programs
4. Implement escape sequence parsing
5. Gradually add features from the TODO list

## Key Concepts to Research
- Termios API
- Pseudo-terminals (posix_openpt, grantpt, unlockpt)
- Fork/exec system calls
- VT100/ANSI escape codes
- Select/poll for I/O multiplexing
- Terminal capabilities (termcap/terminfo)

## Example Escape Sequences
- `\x1b[A` - Cursor up
- `\x1b[B` - Cursor down
- `\x1b[C` - Cursor right
- `\x1b[D` - Cursor left
- `\x1b[2J` - Clear screen
- `\x1b[H` - Move to home position

## Resources
- `man termios`, `man pty`, `man tty_ioctl`
- VT100 User Guide
- ANSI Escape Code standards
- xterm source code (for reference)
