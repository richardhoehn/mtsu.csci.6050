# What: Make File for Final Project
# By:   Richard Hoehn
# When: 2024-12-08

## Compiler and flags
CC = gcc
CFLAGS = -Wall

# Source files and target executables
SOURCES = server.c client.c csapp.c helper.c tictactoe.c
OBJS = $(SOURCES:.c=.o)
TARGETS = server client

# Default target
all: $(TARGETS)

# Build server
server: server.o csapp.o helper.o tictactoe.o
	$(CC) -o $@ $^

# Build client
client: client.o csapp.o helper.o tictactoe.o
	$(CC) -o $@ $^

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJS) $(TARGETS)
