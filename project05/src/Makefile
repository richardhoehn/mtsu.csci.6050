# What: Make File for Project 3
# By:   Richard Hoehn
# When: 2024-10-23

# Compiler and flags
CC = gcc
CFLAGS = -Wall

# Target executables
TARGETS = server client

# Source files
SOURCES = server.c client.c csapp.c helper.c

# Object files
OBJS = $(SOURCES:.c=.o)

# All: build both executables
all: $(TARGETS)

# Build server executable
server: server.o csapp.o helper.o
	$(CC) -o server server.o csapp.o helper.o

# Build client executable
client: client.o csapp.o helper.o
	$(CC) -o client client.o csapp.o helper.o

# Clean: remove object files and executables
clean:
	rm -f $(OBJS) $(TARGETS)