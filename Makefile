CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
LDFLAGS = -lGL -lGLU -lglut -lm

SRC = $(wildcard src/engine/*.c)
OBJ = $(SRC:.c=.o)

all: engineering_tool

engineering_tool: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ) engineering_tool

