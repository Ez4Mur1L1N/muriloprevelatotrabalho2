# Nome do executável. 
TARGET = ted

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -std=c99 -Wall -Wextra -g

# Diretórios
# SRC_DIR = . significa "os arquivos .c estão aqui, nesta pasta"
SRC_DIR = .
# BUILD_DIR = ../build significa "crie a pasta de objetos .o na pasta raiz"
BUILD_DIR = ../build

# Encontra todos os arquivos .c e cria a lista de .o correspondente
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Regra padrão
all: $(TARGET)

# Regra para criar os arquivos de objeto na pasta build
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para criar o executável na pasta raiz
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) -lm

# Limpa a pasta build e o executável
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean