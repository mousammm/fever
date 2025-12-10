CC=gcc
CFLAGS=-Wall -Wextra -I./src/includes
LDLIBS = -lutil
BINARY=fever
SRCDIR=src
BINDIR=bin

SRCS=$(wildcard $(SRCDIR)/*.c)

OBJS=$(patsubst $(SRCDIR)/%.c, $(BINDIR)/%.o, $(SRCS))

all: $(BINDIR)/$(BINARY)

$(BINDIR):
	mkdir -p $(BINDIR)

$(BINDIR)/$(BINARY): $(OBJS)
	@echo "Linking $@"
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(BINDIR)/%.o: $(SRCDIR)/%.c | $(BINDIR)
	@echo "Compiling $< -> $@"
	$(CC) $(CFLAGS) -c -o $@ $< $(LDLIBS)

run: $(BINDIR)/$(BINARY)
	./$(BINDIR)/$(BINARY)

clean:
	rm -rf $(BINDIR)

.PHONY: all run clean
