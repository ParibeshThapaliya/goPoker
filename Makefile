CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC_DIR = src
OBJ_DIR = bin
OBJ = $(OBJ_DIR)/main.o
all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(OBJ_DIR)/poker
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ_DIR)/poker $(OBJ_DIR)/*.o
