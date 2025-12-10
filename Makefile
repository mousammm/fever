CC=gcc
CFLAGS=-Wall -Wextra -g -I./src/includes
LDLIBS = -lutil -lX11
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
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDLIBS)

$(BINDIR)/%.o: $(SRCDIR)/%.c | $(BINDIR)
	@echo "Compiling $< -> $@"
	$(CC) $(CFLAGS) -c -o $@ $< 

run: $(BINDIR)/$(BINARY)
	./$(BINDIR)/$(BINARY)

clean:
	rm -rf $(BINDIR)

.PHONY: all run clean
