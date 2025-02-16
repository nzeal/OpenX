# Compiler and flags
CC = gcc
CFLAGS = -fopenmp -foffload=nvptx-none -O3

# Source and target
SRC = patch.c
OUT = patch

# Rule to build the executable
$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

# Clean up generated files
clean:
	rm -f $(OUT)

.PHONY: clean

