CC=gcc
CFLAGS=-Wall -Wextra -I.
SRCDIR=src
BINARY=fever
BINDIR=bin

# find all src/*.c files
# SRCS src/main.c src/utils.c src/parser.c
SRCS=$(wildcard $(SRCDIR)/*.c)

# convert .c -> .o in bin/
# bin/main.o    bin/utils.o    bin/parser.o
OBJS=$(patsubst $(SRCDIR)/%.c, $(BINDIR)/%.o, $(SRCS))

# default target
all: $(BINDIR)/$(BINARY)

# create binaries dir
$(BINDIR):
	mkdir -p $(BINDIR)

# link .o -> executable
$(BINDIR)/$(BINARY): $(OBJS)
	@echo "Linking $@"
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# compile .c -> .o in bin/
# Compile src/main.c → bin/main.o
# | now recompile only when src changes
# bin/main.o src/main.c
$(BINDIR)/%.o: $(SRCDIR)/%.c | $(BINDIR)
	@echo "Compiling $< -> $@"
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(BINDIR)/$(BINARY)
	./$(BINDIR)/$(BINARY)

clean:
	rm -rf $(BINDIR)

.PHONY: all run clean
