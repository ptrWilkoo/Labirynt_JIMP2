# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99

# Source files
SRCS = modules/input.c modules/solver.c modules/output.c modules/main.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
EXEC = program

# Default target
all: $(EXEC)

# Linking
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilation
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean
clean:
	rm -f $(EXEC) $(OBJS)

