#ifndef CHECKWIN_H
#define CHECKWIN_H
#include <stdbool.h>
#include "Structures.h"
void checkHands(Player playersList[10], Card *boardCards);

int compareHighCard(Card *player1, Card *player2);
void checkWinner(Player playersList[10], Card *communityCards);

bool isFlush(Card *cards, int numCards);

bool isStraight(Card *cards, int numCards);

int compareCards(const void *a, const void *b);

int isRoyalFlush(Card *cards, int numCards);

int isStraightFlush(Card *cards, int numCards);

int checkStraightOrRoyalFlush(Card *cards, int numCards);

#endif
