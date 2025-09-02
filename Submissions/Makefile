# ============================================================================
# Makefile for C Programming
# File: Makefile (capital M, no extension)
#
# Instructions:
# 1. Change TARGET to your desired executable name
# 2. List your .c files in SOURCES
# 3. List your .h files in HEADERS (if any)
# 4. Type 'make' to build your program
# ============================================================================
# Compiler settings


CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -g -O0


# Project settings - MODIFY THESE FOR YOUR PROJECT


TARGET = fuel_station
SOURCES = fuel_station.c
HEADERS = 


# If you don't have header files, just leave HEADERS empty: HEADERS =
# ============================================================================
# Build Rules
# ============================================================================
# Default target - this runs when you type 'make'
# The 'all' rule is a convention that builds the main program


all: $(TARGET)

# Main build rule - creates your executable

$(TARGET): $(SOURCES) $(HEADERS)
	@echo "Building $(TARGET)..."
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)
	@echo "Build successful! Run with: ./$(TARGET)"

# Run the program after building
run: $(TARGET)
	./$(TARGET)


# Clean up generated files
clean:
	@echo "Cleaning up..."
	rm -f $(TARGET) *.o
	@echo "Cleanup complete."


# Rebuild everything from scratch
rebuild: clean all


# Show available commands
help:
	@echo "Available commands:"
	@echo " make - Build the program"
	@echo " make run - Build and run the program"
	@echo " make clean - Remove generated files"
	@echo " make rebuild - Clean and build from scratch"


# Declare phony targets (targets that don't create files)
.PHONY: all run clean rebuild help
