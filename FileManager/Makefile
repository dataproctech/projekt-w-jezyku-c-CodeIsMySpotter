# Kompilator i flagi
CC = gcc
CFLAGS = -Wall -Wextra -MMD -MP
LDFLAGS = `pkg-config --libs gtk+-3.0`
PKG_CFLAGS = `pkg-config --cflags gtk+-3.0`

# Katalogi
SRC_DIR = src
OBJ_DIR = build

# Automatyczne zbieranie plików źródłowych
SRCS = $(shell find $(SRC_DIR) -name '*.c')
# Automatyczne generowanie listy katalogów nagłówków
INC_DIRS = $(shell find $(SRC_DIR) -type d)
CFLAGS += $(addprefix -I, $(INC_DIRS)) $(PKG_CFLAGS)

# Pliki obiektowe - zachowanie struktury katalogów
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

# Nazwa pliku wynikowego
TARGET = $(OBJ_DIR)/main.exe

# Domyślny cel
all: $(TARGET)

# Linkowanie
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Kompilacja z tworzeniem katalogów
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Dołączanie zależności
-include $(DEPS)

# Czyszczenie
clean:
	rm -rf $(OBJ_DIR)

.PHONY: all clean
