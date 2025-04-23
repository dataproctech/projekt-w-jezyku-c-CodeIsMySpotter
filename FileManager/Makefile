# Kompilator i flagi
CC = gcc
CFLAGS = -Wall -Wextra `pkg-config --cflags gtk+-3.0`
LDFLAGS = `pkg-config --libs gtk+-3.0`

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

# Tworzenie katalogu build (jeśli nie istnieje)
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Czyste buildy
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
