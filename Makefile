CC = gcc
CFLAGS = -Wall -g -std=c11
LDFLAGS = -lglfw -lGL -ldl -lm

VERSION = 0.0.1
# Source files
SRC = grphicPipe.c src/glad.c
# Object files
OBJ = $(SRC:.c=.o)
# Final executable
EXEC = ice

all: $(EXEC)

# Compiling Open GL loader 
$(EXEC): $(OBJ)

	@echo "Building $(EXEC) version $(VERSION)..."
	$(CC) -o $@ $^ $(LDFLAGS)

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

