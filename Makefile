VERSION = 0.0.1

CC = gcc
CFLAGS = -Wall -g -std=c11 
LDFLAGS = -lSDL2 -lGL -ldl -lm 

# Source files
SRC = main.c core/glad.c core/iceCreamRender.c core/internalRender.c core/iceCreamGlobal.c core/io.c core/iceCreamRenderUtil.c core/time/time.c core/iceConfig/config.c core/input.c
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

