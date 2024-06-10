CC = gcc
CFLAGS = -Wall -Wextra -std=c99 $(shell pkg-config --cflags gtk+-2.0)
LDFLAGS = $(shell pkg-config --libs gtk+-2.0)
SRC_DIR = src
OBJ_DIR = bin
OBJ_GUI = $(OBJ_DIR)/client.o $(OBJ_DIR)/GUI.o $(OBJ_DIR)/structures.o $(OBJ_DIR)/GameHandling.o $(OBJ_DIR)/CheckWin.o
OBJ_SERVER = $(OBJ_DIR)/server.o $(OBJ_DIR)/structures.o $(OBJ_DIR)/GameHandling.o $(OBJ_DIR)/CheckWin.o

all: gui server

gui: $(OBJ_GUI)
	$(CC) $(CFLAGS) $(OBJ_GUI) -o $(OBJ_DIR)/poker-gui $(LDFLAGS)

server: $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -o $(OBJ_DIR)/poker-server

$(OBJ_DIR)/structures.o: $(SRC_DIR)/Structures.c $(SRC_DIR)/Structures.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/client.o: $(SRC_DIR)/client.c $(SRC_DIR)/Structures.h $(SRC_DIR)/GameHandling.h $(SRC_DIR)/CheckWin.h $(SRC_DIR)/GUI.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/server.o: $(SRC_DIR)/server.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/GUI.o: $(SRC_DIR)/GUI.c $(SRC_DIR)/GUI.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/GameHandling.o: $(SRC_DIR)/GameHandling.c $(SRC_DIR)/GameHandling.h $(SRC_DIR)/Structures.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/CheckWin.o: $(SRC_DIR)/CheckWin.c $(SRC_DIR)/CheckWin.h $(SRC_DIR)/Structures.h
	$(CC) $(CFLAGS) -c $< -o $@

tar:
	tar -czvf Poker_Alpha_src.tar.gz README INSTALL COPYRIGHT bin doc src Makefile

test-gui:
	./bin/poker-gui $(NAME)

clean:
	rm -f $(OBJ_DIR)/poker-gui $(OBJ_DIR)/poker-server $(OBJ_DIR)/*.o

test:
	./bin/poker-server