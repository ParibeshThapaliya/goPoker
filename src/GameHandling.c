void shuffleDeck(Card deck[52]) {
    for (int i = 0; i < 52; i++) {
        int r = rand() % 52;
        Card temp = deck[i];
        deck[i] = deck[r];
        deck[r] = temp;
    }
}

void dealCards(Card deck[52], Player playersList[10]) {
    int cardIndex = 0;
    for (int i = 0; i < 10; i++) {
        if (playersList[i].status == 1) {
            for (int j = 0; j < 2; j++) {
                playersList[i].handCards[j] = deck[cardIndex++];
            }
        }
    }
}

void handlePlayerMove(Player* player, ACTION action, int raiseAmount, int betAmount) {
    switch (action) {
        case CHECK:
            if(betAmount>0){
                printf("Cannot check when there is an ongoing bet of %d.\n", betAmount);
                break;
            }
            printf("%s checks.\n", player->name);
            // Implement logic for check if necessary
            break;
        case RAISE:
            if (raiseAmount > player->points) {
                printf("%s cannot raise by %d points, not enough points.\n", player->name, raiseAmount);
                break;
            }
            player->points -= raiseAmount;
            printf("%s raises by %d points. Remaining points: %d\n", player->name, raiseAmount, player->points);
            // Implement logic to handle the raise in the game context
            break;
        case FOLD:
            player->status = 0; // Set status to folded
            printf("%s folds.\n", player->name);
            // Implement logic to handle fold if necessary
            break;
        case CALL:
            if(betAmount > player->points){
                //all in we need to handle that
            }
            else{
                player->points -= betAmount;
                printf("%s calls.\n", player->name);
            }
        default:
            printf("Invalid action.\n");
            break;
    }
}