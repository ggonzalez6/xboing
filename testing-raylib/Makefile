# Variables
CFLAGS := $(shell pkg-config --cflags raylib)
LDFLAGS := $(shell pkg-config --libs raylib) -framework OpenGL -framework Cocoa -framework IOKit
CC := gcc

# Source files
SRC := balltest_main.c ball.c
OBJ := balltest_main.o ball.o
EXE := balltest

# Default target
all: $(EXE)

# Link the executable
$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(CFLAGS) $(LDFLAGS)

# Compile each .c file into .o file
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Clean target
clean:
	rm -f $(OBJ) $(EXE)
