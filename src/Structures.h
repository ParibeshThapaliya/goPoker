//This file has the headers for the caard and player structuees
#include<constants.h>
//Data structures
typedef struct {
    SUIT suit;
    RANK rank;
} Card;

Card Deck[52];
Card boardCards[5];

typedef struct {
    char name[50];
    int points;
    int seat;
    int socket;
    int status;
    int connection;
    HAND hand;
    Card handCards[2];
} Player;

Player PlayersList[10];

Player* createPlayer(const char* name, int points, int seat, int socket);

void deletePlayer(Player* player);

//functions
Card* createCard(SUIT suit, RANK rank);

void deleteCard(Card* card);

void initializeDeck(Card deck[52]);

Player* createPlayer(const char* name, int points, int seat, int socket);

void deletePlayer(Player* player);

void initializePlayers(Player playersList[], int numPlayers);