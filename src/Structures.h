// This file has the headers for the caard and player structuees

// Data structures
#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef enum
{
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
} RANK;
typedef enum
{
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
} SUIT;
typedef enum
{
    NONE,
    HighCard,
    OnePair,
    TwoPair,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush,
    RoyalFlush
} HAND;
typedef enum
{
    CHECK,
    RAISE,
    FOLD,
    CALL
} ACTION;

typedef struct
{
    SUIT suit;
    RANK rank;
} Card;

Card Deck[52];
Card boardCards[5];
int pot;
typedef struct
{
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

Player *createPlayer(const char *name, int points, int seat, int socket);

void deletePlayer(Player *player);

// functions
Card *createCard(SUIT suit, RANK rank);

void deleteCard(Card *card);

void initializeDeck(Card deck[52]);

void deletePlayer(Player *player);

void initializePlayers(Player playersList[], int numPlayers);

#endif
