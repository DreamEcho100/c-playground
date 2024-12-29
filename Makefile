CC = gcc           # Compiler to use
CFLAGS = -Wall      # Compiler flags (show all warnings)
LDFLAGS =           # Linker flags (if needed)

# Source files and object files
SRCS = main.c strings/strings_utils.c arrays/arrays_utils.c
OBJS = $(SRCS:.c=.o)

# Output executable
OUT = main

# Default target
all: $(OUT)

# Rule to link the object files and create the final executable
$(OUT): $(OBJS)
	$(CC) $(OBJS) -o $(OUT)

# Rule to compile each .c file into a .o file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove compiled files
clean:
	rm -f $(OBJS) $(OUT)

# Install rule (optional, if you want to copy files to system directories)
install:
	cp $(OUT) /usr/local/bin/

# Phony targets (these are not actual files)
.PHONY: all clean install

# make && clear && ./main && make clean;