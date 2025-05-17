# Kompilator i flagi
CC = gcc
CFLAGS = -Wall -Wextra -MMD -MP `pkg-config --cflags gtk+-3.0`
LDFLAGS = `pkg-config --libs gtk+-3.0`

# Katalogi i pliki
SRC_DIR = src
OBJ_DIR = build
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Nazwa programu
TARGET = build/main.exe

# Domyślny cel
all: $(TARGET)

# Linkowanie finalnego pliku wykonywalnego
$(TARGET): $(OBJS) | $(OBJ_DIR)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Kompilacja plików źródłowych do obiektowych z generowaniem zależności
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Tworzenie katalogu build, jeśli nie istnieje
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Dołączenie plików zależności (.d)
-include $(OBJS:.o=.d)

# Czyszczenie builda
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
