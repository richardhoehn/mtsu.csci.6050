# What: Make File for Lab 9
# By:   Richard Hoehn
# When: 2024-10-24

# Compiler and flags
CC = gcc
CFLAGS = -Wall

# Target executables
TARGETS = server client

# Source files
SOURCES = server.c client.c csapp.c

# Object files
OBJS = $(SOURCES:.c=.o)

# All: build both executables
all: $(TARGETS)

# Build server executable
server: server.o csapp.o
	$(CC) -o server server.o csapp.o

# Build client executable
client: client.o csapp.o
	$(CC) -o client client.o csapp.o

# Clean: remove object files and executables
clean:
	rm -f $(OBJS) $(TARGETS)