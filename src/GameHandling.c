#include "Structures.h"
#include "GameHandling.h"
#include "constants.h"
#include "time.h"

void shuffleDeck(Card deck[52]) {
    srand(time(NULL));
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

void printHand(Player playersList[10]){
	for(int i = 0;i<10; i++){
		printf("%s has the following hand %d %d, %d %d.\n", playersList[i].name, (playersList[i].handCards[0].rank), (playersList[i].handCards[0].suit), (playersList[i].handCards[1].rank), (playersList[i].handCards[1].suit));
	}
}

void printCommunityCards(Card *communityCards, int numCards){
	for(int i=0; i<numCards; i++){
		
			printf("%d %d\t", communityCards[i].rank, communityCards[i].suit);
		
	}
	printf("\n\n");
}
int handlePlayerMove(int pos, ACTION action, int raiseAmount, int betAmount) {
    switch (action) {
        case CHECK:
            if(betAmount>0){
                printf("Cannot check when there is an ongoing bet of %d.\n", betAmount);
                return 0;
            }
            printf("%s checks.\n", PlayersList[pos].name);
            // Implement logic for check if necessary
            break;

        case RAISE:
            if (raiseAmount > PlayersList[pos].points) {
		//ALL IN
                printf("%s, you cannot raise more than you have\n", PlayersList[pos].name);
                return 0;
            }
            PlayersList[pos].points -= raiseAmount;
	    pot += raiseAmount;
            printf("%s raises by %d points. Remaining points: %d\n", PlayersList[pos].name, raiseAmount, PlayersList[pos].points);
            // Implement logic to handle the raise in the game context
            break;
        case FOLD:
            PlayersList[pos].status = 0; // Set status to folded
            printf("%s folds.\n", PlayersList[pos].name);
            // Implement logic to handle fold if necessary
            break;
        case CALL:
            if(betAmount > PlayersList[pos].points){
                pot += PlayersList[pos].points;
		PlayersList[pos].points = 0;
            }
            else{
                PlayersList[pos].points -= betAmount;
                printf("%s calls. Remaining points are %d\n", PlayersList[pos].name, PlayersList[pos].points);
            }
	    break;
        default:
            printf("Invalid action.\n");
	    return 0;
    }
    return 1;
}

int GameEnd(){
	int count = 0;
	for(int i=0; i<10; i++){
		if(PlayersList[i].status == 1){
			count++;
		}
		else{
			continue;
		}
	}
	if(count<=1){
		return 1;
	}
	else{
		return 0;
	}
}
