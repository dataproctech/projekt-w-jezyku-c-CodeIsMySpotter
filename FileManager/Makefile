# Kompilator i flagi
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Pliki źródłowe i obiektowe
SRC_DIR = src
OBJ_DIR = build
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Nazwa programu
TARGET = build/main


# Domyślny cel
all: $(TARGET)

# Kompilacja programu
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

# Kompilacja plików .c do .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Tworzenie katalogu build/ jeśli nie istnieje
$(OBJ_DIR):
	if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)

