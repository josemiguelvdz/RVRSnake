# Directories
# S_DIR=source
B_DIR=Exe

# Files
S_FILES=$(shell find "../" -type f -iname '*.cc')

# Header files
H_FILES=$(shell find "../" -type f -iname '*.h')

# Output
EXEC=$(B_DIR)/SnakeTest

# Build settings
CC=g++
CFLAGS=#-g -I. -std=c++11
LIBS=-lpthread -lSDL2
WITHOUT_WARNINGS=-w

all:
	mkdir -p $(B_DIR)
	$(CC) $(WITHOUT_WARNINGS) $(S_FILES) -o $(CFLAGS) $(EXEC) $(LIBS)

exe:
	./$(EXEC)

clean:
	rm -rf $(B_DIR)/*