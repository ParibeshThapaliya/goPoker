//This file is to declare all the constants
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
typedef enum {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE} RANK;
typedef enum {CLUBS, DIAMONDS, HEARTS, SPADES} SUIT;
typedef enum {NONE, HighCard, OnePair, TwoPair, ThreeOfAKind, Straight, Flush, FourOfAKind, StraightFlush, RoyalFlush} HAND;
typedef enum {CHECK, RAISE, FOLD, CALL} ACTION;