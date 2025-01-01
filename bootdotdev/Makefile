# Makefile for compiling and running all C files (including nested ones).
# It links the math library and handles nested directories automatically.

# The compiler to use
CC = gcc

# Flags for the compiler
# -Wall enables all warnings.
# -Wextra enables additional warnings.
# -g includes debugging information (useful during development).
# -lm links the math library.
CFLAGS = -Wall -Wextra -g

# The name of the final executable
OUTPUT = main

# Use `find` to locate all C files in the current directory and subdirectories.
# The result is stored in the variable SRCS.
SRCS = $(shell find . -name "*.c")

# Automatically create a list of object files (.o) from the source files (.c).
# Each .c file will have a corresponding .o file.
OBJS = $(SRCS:.c=.o)

# Default target: build the program
# This is the target that runs when you simply type `make`.
all: $(OUTPUT)

# Rule to link all object files into the final executable
$(OUTPUT): $(OBJS)
	@echo "Linking object files to create the executable..."
	$(CC) $(CFLAGS) $(OBJS) -o $(OUTPUT) -lm
	@echo "Build complete. You can run the program with './$(OUTPUT)'"

# Rule to compile .c files into .o files
# $< represents the first dependency (the .c file).
# $@ represents the target (the .o file).
%.o: %.c
	@echo "Compiling $< into $@..."
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to run the program
# This lets you type `make run` to execute the compiled program.
run: $(OUTPUT)
	@echo "Running the program..."
	./$(OUTPUT)

# Rule to clean up generated files
# This removes the executable and all object files.
# Type `make clean` to use this.
clean:
	@echo "Cleaning up..."
	rm -f $(OUTPUT) $(OBJS)
	@echo "Clean complete."

# Special rule to ensure clean builds if needed
# .PHONY tells make that these targets are not actual files.
.PHONY: all run clean

# make && ./main && make clean