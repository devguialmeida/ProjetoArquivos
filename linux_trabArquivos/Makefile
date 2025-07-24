SRC_DIR := src
BIN_DIR := bin

CC := gcc
CFLAGS := -Wall -Wextra -O2

# Lista de fontes e executáveis
SRCS := $(wildcard $(SRC_DIR)/*.c)
EXES := $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%, $(SRCS))

all: $(BIN_DIR) $(EXES)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/%: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(BIN_DIR)

run:
	@if [ -z "$(PROG)" ]; then \
		echo "Use: make run PROG=nome_do_programa [ARGS=\"argumentos\"]"; \
		exit 1; \
	fi
	@if [ ! -x "$(BIN_DIR)/$(PROG)" ]; then \
		echo "Executável '$(BIN_DIR)/$(PROG)' não encontrado! Compile com 'make' primeiro."; \
		exit 1; \
	fi
	@echo Executando: ./$(BIN_DIR)/$(PROG) $(ARGS)
	@./$(BIN_DIR)/$(PROG) $(ARGS)

.PHONY: all clean run
