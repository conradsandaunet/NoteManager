SRCDIR = src
OBJDIR = obj

CC = gcc
CFLAGS = -O2 -Wall -Wextra -std=c11 -I$(SRCDIR)

_DEPS = notes.h ui.h util.h
DEPS = $(patsubst %,$(SRCDIR)/%,$(_DEPS))

_OBJS = main.o notes.o ui.o util.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

all: notemanager.exe

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS) | $(OBJDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

notemanager.exe: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: all clean

clean:
	rm -f $(OBJDIR)/*.o notemanager.exe