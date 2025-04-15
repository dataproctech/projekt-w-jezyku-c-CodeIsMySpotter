# Kompilator i flagi
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -Llib -lglfw3 -lopengl32 -lgdi32

# Pliki źródłowe i obiektowe
SRC_DIR = src
OBJ_DIR = build
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Nazwa programu
TARGET = build/main.exe

# Domyślny cel
all: $(TARGET)

# Kompilacja programu
$(TARGET): $(SRCS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)
	

# Kompilacja plików .c do .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

