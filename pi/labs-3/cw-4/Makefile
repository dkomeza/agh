# Kompilator i flagi
CC = gcc
CFLAGS = -std=c2x

# Katalogi
SRC_DIR = src
BIN_DIR = bin
LIB_DIR = lib
TEST_DIR = tests

# Pliki źródłowe i obiektowe
SRCS := $(shell find $(SRC_DIR) -name *.cpp -or -name *.c -or -name *.s)
OBJS = $(SRCS:%.c=$(BIN_DIR)/%.o)
TARGET = $(BIN_DIR)/app

# Domyślna reguła
all: $(TARGET)

# Kompilacja głównego programu
$(TARGET): $(OBJS) $(LIBRARY)
	@$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Kompilacja plików .c do .o
$(BIN_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@


run: $(TARGET)
	@./$(TARGET)
# Czyszczenie plików tymczasowych
clean:
	rm -f $(OBJS) $(LIB_OBJS) $(TARGET) $(TEST_TARGET) $(LIBRARY)
