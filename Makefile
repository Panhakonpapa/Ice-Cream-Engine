CC = gcc
CFLAGS = -Wall -g -std=c11 
LDFLAGS = -lglfw -lGL -ldl -lm

# -Wpedantic -fsanitize=undefined -fsanitize=address 
VERSION = 0.0.1
# Source files
SRC = main.c core/OpenGL.c core/iceCreamRender.c core/Math.c core/Entity.c 

# Object files
OBJ = $(SRC:.c=.o)
# Final executable
EXEC = ice

all: $(EXEC)

# Compiling Open GL loader 
$(EXEC): $(OBJ)

	$(CC) -o $@ $^ $(LDFLAGS)

#Compile source files 
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ) $(EXEC)

