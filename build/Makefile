# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -g

# Libraries
LIBS = -lm -lGL -lGLEW -lglfw -lGLU

# Directories
SRC_DIR = ../src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = ../src/include
ENGINE_DIR = $(SRC_DIR)/engine
FILE_MANAGER_DIR = $(SRC_DIR)/file_manager
RENDER_DIR = $(SRC_DIR)/render

# Output Executable
TARGET = $(BIN_DIR)/engineering_tool

# Source Files
SRC = $(SRC_DIR)/main.c \
      $(ENGINE_DIR)/bsp_node.c \
      $(ENGINE_DIR)/polyhedron.c \
      $(ENGINE_DIR)/menu.c \
      $(FILE_MANAGER_DIR)/save_file.c \
      $(ENGINE_DIR)/properties.c \
      $(RENDER_DIR)/render_engine.c

# Object Files
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# Include Headers
INCLUDES = -I$(INCLUDE_DIR)

# Default Target
all: build_dirs $(TARGET)

# Compile Target
$(TARGET): $(OBJ)
	@echo "Linking $@"
	$(CC) $(CFLAGS) -o $@ $^ $(INCLUDES) $(LIBS)

# Build Object Files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "Compiling $<"
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

# Directory Setup
build_dirs:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)/$(SRC_DIR)
	@mkdir -p $(OBJ_DIR)/$(ENGINE_DIR)
	@mkdir -p $(OBJ_DIR)/$(FILE_MANAGER_DIR)
	@mkdir -p $(OBJ_DIR)/$(RENDER_DIR)

# Clean Up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run Executable
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
