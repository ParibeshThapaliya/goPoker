//This file is created for all the functions that are used to ensure the game runs
#ifndef GAMEHANDLING_H
#define GAMEHANDLING_H

#include "Structures.h"
void shuffleDeck(Card deck[52]);

void dealCards(Card deck[52], Player playersList[10]);

int handlePlayerMove(int pos, ACTION action, int raiseAmount, int betAmount);

void printCommunityCards(Card *communityCards, int numCards);
void printHand(Player playersList[10]);

int GameEnd();
#endif
