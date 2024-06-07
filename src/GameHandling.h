//This file is created for all the functions that are used to ensure the game runs

void shuffleDeck(struct Card deck[52]);

void dealCards(struct Card deck[52], struct Player playersList[10]);

void handlePlayerMove(Player* player, ACTION action, int raiseAmount, int betAmount);
