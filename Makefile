CC = gcc
CFLAGS = -Wall -Wextra -std=c99 $(shell pkg-config --cflags gtk+-2.0)
LIFLAGS= $(shell pkg-config --libs gtk+-2.0)
SRC_DIR = src
OBJ_DIR = bin
OBJ_GUI = $(OBJ_DIR)/main.o $(OBJ_DIR)/client.o $(OBJ_DIR)/GUI.o $(OBJ_DIR)/server.o
OBJ_SERVER =$(OBJ_DIR)/server.o
all: gui server
gui: $(OBJ_GUI)
	$(CC) $(CFLAGS) $(OBJ_GUI) -o $(OBJ_DIR)/poker-gui $(LIFLAGS)
server:$(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -o $(OBJ_DIR)/poker-server 
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
test-gui:
	./bin/poker-server
clean:
	rm -f $(OBJ_DIR)/poker $(OBJ_DIR)/*.o
test:
	./bin/poker-gui