Card* createCard(SUIT suit, RANK rank) {
    Card* card = (Card*)malloc(sizeof(Card));
    card->suit = suit;
    card->rank = rank;
    return card;
}

void deleteCard(Card* card) {
    free(card);
}

void initializeDeck(Card deck[52]) {
    int i = 0;
    for(int i=0; i<52; i++){
        deck[i] = createCard(TWO, CLUBS);
    }
    for (SUIT suit = CLUBS; suit <= SPADES; suit++) {
        for (RANK rank = TWO; rank <= ACE; rank++) {
            deck[i].suit = suit;
            deck[i].rank = rank;
            i++;
        }
    }
}

Player* createPlayer(const char* name, int points, int seat, int socket) {
    Player* player = (Player*)malloc(sizeof(Player));
    strcpy(player->name, name);
    player->points = points;
    player->seat = seat;
    player->socket = socket;
    player->status = 1;
    player->hand = NONE;
    return player;
}

void deletePlayer(Player* player) {
    free(player);
}

//We have to update this function
void initializePlayers(Player playersList[], int numPlayers) {
    for (int i = 0; i < numPlayers; i++) {
        printf("Enter name for player %d: ", i + 1);
        scanf("%s", playersList[i].name);
        playersList[i].points = 1000; // Initial points
        playersList[i].seat = i + 1;
        playersList[i].socket = i + 1; // Placeholder for socket
        playersList[i].status = 1; // Active status
        playersList[i].hand = NONE;
    }
}12