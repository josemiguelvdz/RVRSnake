# Directories
# S_DIR=source
B_DIR=Exe

# Files
S_FILES=Snake.cc

# Header files
H_FILES=

# Output
EXEC=$(B_DIR)/SnakeTest

# Build settings
CC=g++
LIBS=-lpthread -lSDL2

all:
	mkdir -p $(B_DIR)
	$(CC) $(S_FILES) -o $(EXEC) $(LIBS)

exe:
	./$(EXEC)

clean:
	rm -rf $(B_DIR)/*