CC = gcc
CFLAGS = -Wall -Wextra -std=c99 $(shell pkg-config --cflags gtk+-4.0)
LIFLAGS= $(shell pkg-config --libs gtk+-4.0)
SRC_DIR = src
OBJ_DIR = bin
OBJ = $(OBJ_DIR)/main.o $(OBJ_DIR)/client.o $(OBJ_DIR)/gui.o $(OBJ_DIR)/server.o
all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(OBJ_DIR)/poker $(LDFLAGS)
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/client.o: $(SRC_DIR)/client.c $(SRC_DIR)/client.h
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/server.o: $(SRC_DIR)/server.c $(SRC_DIR)/server.h
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/GUI.o: $(SRC_DIR)/GUI.c $(SRC_DIR)/GUI.o $(SRC_DIR)/client.h
	$(CC) $(CFLAGS) -c $< -o $@
tar:
	tar -czvf Poker_Alpha_src.tar.gz README INSTALL COPYRIGHT bin doc src Makefile
clean:
	rm -f $(OBJ_DIR)/poker $(OBJ_DIR)/*.o
test:
	./bin/poker