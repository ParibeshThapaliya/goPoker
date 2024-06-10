#include "CheckWin.h"
#include "GameHandling.h"
#include "Structures.h"
void checkHands(Player playersList[10], Card *boardCards) {
    // This function should evaluate the hands and set the hand type for each player.
    // For simplicity, we'll assume all players have HighCard.
    for (int i = 0; i < 10; i++) {
        if (playersList[i].status == 1) {
            playersList[i].hand = HighCard; // Placeholder logic
        }
    }

    Card checkBoard[7];
    for (int i = 0; i<5; i++){
        checkBoard[i] = boardCards[i];
    }

    for(int i=0; i<10; i++){
	if(playersList[i].status == 1){
        	for(int j = 5; j<7; j++){
            		checkBoard[j] = playersList[i].handCards[j-5];
        	}
		int rankCounts[13] = {0};
    		for (int i = 0; i < 7; i++) {
        		rankCounts[checkBoard[i].rank]++;
    		}

    		// Check for four of a kind, full house, three of a kind, two pair, one pair
         	int fourOfAKind = 0, threeOfAKind = 0, pairs = 0;
             	for (int i = 0; i < 13; i++) {
                     if (rankCounts[i] == 4) {
                     	fourOfAKind = 1;
                     } else if (rankCounts[i] == 3) {
                        threeOfAKind = 1;
                     } else if (rankCounts[i] == 2) {
                        pairs++;
                     }
                }	

        	//Fisrt check for royal flush
		if(checkStraightOrRoyalFlush(checkBoard, 7) == 2){
			playersList[i].hand = RoyalFlush;
		}
        	//Second check for Straight FLush
       		if(checkStraightOrRoyalFlush(checkBoard, 7) == 1){
            		//Add more logic since some card can form a flush while others may form a straight
            		playersList[i].hand = StraightFlush;
            		continue;
        	}
        	//Third check for Four of a Kind
        	if(fourOfAKind){
			playersList[i].hand = FourOfAKind;
		}
		//Check for full house
		if(threeOfAKind && pairs){
			playersList[i].hand = FullHouse;
		}
        	//Fifth check for Flush
        	if(isFlush(checkBoard, 7)){
            		playersList[i].hand = Flush;
            		continue;
        	}
        	//Sixth check for Straight
        	if(isStraight(checkBoard, 7)){
            		playersList[i].hand = Straight;
            	continue;
        	}
        	//Seventh check for Three of A Kind
		if(threeOfAKind){
			playersList[i].hand = ThreeOfAKind;
		}
        	//Eight check for Two Pair
		if(pairs == 2){
			playersList[i].hand = TwoPair;
		}
		if(pairs == 1){
			playersList[i].hand = OnePair;
		}
        
        	//Tenth check for high card 
    	}
    }	
}

int compareHighCard(Card *player1, Card *player2){
		if(((player1[0].rank>player2[0].rank) && (player1[0].rank > player2[1].rank)) || ((player1[1].rank>player2[0].rank) && (player1[1].rank > player2[1].rank))){
			return 1;
		}
		else if(((player2[0].rank>player1[0].rank) && (player2[0].rank > player1[1].rank)) || ((player2[1].rank>player1[0].rank) && (player2[1].rank > player1[1].rank))){
			return 2;
		}
		else{
			return 0;
		}
	   
}
void checkWinner(Player playersList[10], Card *communityCards) {
    int winnerIndex = 0;
    int split = 0;
    for (int i = 1; i < 10; i++) {
        if (playersList[i].status == 1 && playersList[i].hand > playersList[winnerIndex].hand) {
            winnerIndex = i;
	    split = 0;
	    continue;
	}
	else if (playersList[i].status == 1 && (playersList[i].hand == playersList[winnerIndex].hand)) {
            
	    //Computing certain things for checking other hands
            int rankcount1[13] = {0};
	    int rankcount2[13] = {0};
	    Card Board1[7];
	    Card Board2[7];

	    for(int k = 0; k<5; k++){
		Board1[k] = communityCards[k];
		Board2[k] = communityCards[k];
	    }
	    for(int j=5; j<7; j++){
		Board1[j] = playersList[winnerIndex].handCards[j-5];
		Board2[j] = playersList[i].handCards[j-5];
	    }	
    	    for (int k = 0; k < 7; k++) {
        	rankcount1[Board1[k].rank]++;
		rankcount2[Board2[k].rank]++;
            }
	    //FOR HIGH CARD
	    if(playersList[winnerIndex].hand == HighCard){
		if(compareHighCard(playersList[winnerIndex].handCards, playersList[i].handCards) == 1){
			break;
		}
		else if(compareHighCard(playersList[winnerIndex].handCards, playersList[i].handCards) == 2){
			winnerIndex = i;
			break;
		}
		else{
			split = i;
			break;
		}
	    }
	    
	    else if(playersList[winnerIndex].hand == OnePair){
		for(int j=12; j>=0; j++){
			if(rankcount1[j] == 2 && rankcount2[j] == 2){
				if(compareHighCard(playersList[winnerIndex].handCards, playersList[i].handCards) == 1){
                        		break;
                		}
                		else if(compareHighCard(playersList[winnerIndex].handCards, playersList[i].handCards) == 2){
                        		winnerIndex = i;
                        		break;
                		}
                		else{
                        		split = i;
                        		break;
                		}
			}
			else if(rankcount1[j] == 2){
				break;
			}
			else if(rankcount2[j] == 2){
				winnerIndex = i;
				break;
			}
			else{
				continue;
			}
		}
	    }

	    //Computing certain things for checking other hands
	    else if(playersList[winnerIndex].hand == TwoPair){
		
		for(int j =12; j>=0; j--){
			if(rankcount1[j] == 2 && rankcount2[j] == 2){
				continue;
			}
			else if(rankcount1[j] == 2){
				break;
			}
			else if(rankcount2[j] == 2){
				winnerIndex = i;
	
			break;
			}
			else if( j == 0 ){
				if(compareHighCard(playersList[winnerIndex].handCards, playersList[i].handCards) == 1){
					break;
				}
				else if(compareHighCard(playersList[winnerIndex].handCards, playersList[i].handCards) == 2){
					winnerIndex = i;
					break;
				}
				else{
					split = i;
					break;
				}
			}
			else{
				continue;
			}
		}	
	    }
	   
	    else if(playersList[winnerIndex].hand == ThreeOfAKind || playersList[winnerIndex].hand == FourOfAKind){
		for(int j =12; j>=0; j--){
			if(rankcount1[j] >=3 && rankcount2[j] >=3){
				continue;
			}
			else if(rankcount1[j] >= 3){
				break;
			}
			else if(rankcount2[j] >= 3){
				winnerIndex = i;
				break;
			}
			else if( j == 0 ){
				if(compareHighCard(playersList[winnerIndex].handCards, playersList[i].handCards) == 1){
					break;
				}
				else if(compareHighCard(playersList[winnerIndex].handCards, playersList[i].handCards) == 2){
					winnerIndex = i;
					break;
				}
				else{
					split = i;
					continue;
				}
			}
			else{
				continue;
			}
		}	
	    }
		
	    else if(playersList[winnerIndex].hand == FullHouse){
		for(int j=12; j>=0; j--){
			if(rankcount1[j] == 3 && rankcount2[j] == 3){
				for(int k=12; k>=0; k--){
					if(rankcount1[k] == 2 && rankcount2[k] == 2){
						split = i;
					}
					else if(rankcount1[k] == 2){
						break;
					}
					else if(rankcount2[k] == 2){
						winnerIndex = i;
						break;
					}
					else{
						continue;
					}
				}
			break;
			}
			else if(rankcount1[j] == 3){
				break;
			}
			else if(rankcount2[j] == 3){
				winnerIndex = i;
				break;
			}
			else{
				continue;
			}
		}
	    }
	    
	    else if(playersList[winnerIndex].hand == Straight){
		for(int j=12; j>=3; j--){
			if(rankcount1[j] == 1 && rankcount1[j-1] == 1 && rankcount1[j-2] == 1 && rankcount2[j] == 1 && rankcount2[j-1] == 1 && rankcount2[j-2] == 1){
				split = i;
			}
			else if(rankcount1[j] == 1 && rankcount1[j-1] == 1 && rankcount1[j-2] == 1){
				break;
			}
			else if( rankcount2[j] == 1 && rankcount2[j-1] == 1 && rankcount2[j-2] == 1){
				winnerIndex = i;
				break;
			}
			else{
				continue;
			}
		}
	   }
	   else{
		if(compareHighCard(playersList[winnerIndex].handCards, playersList[i].handCards) == 1){
              		break;
       		}        	
		else if(compareHighCard(playersList[winnerIndex].handCards, playersList[i].handCards) == 2){
              		winnerIndex = i;
               		break;         	
		}
               	else{
                   	split = i;
           		break;
                }
	  }
	
   }
   }
   if(split == 0){
    	printf("Winner is %s with %d hand.\n", playersList[winnerIndex].name, playersList[winnerIndex].hand);
	playersList[winnerIndex].points += pot;
   }
   else{
	printf("Split pot with %s and %s splitting the pot.\n", playersList[winnerIndex].name, playersList[split].name);
	playersList[winnerIndex].points += pot/2;
	playersList[split].points += pot/2;
   }
   pot = 0;
}

int compareCards(const void *a, const void *b) {
    return ((Card *)a)->rank - ((Card *)b)->rank;
}

bool isStraight(Card *cards, int numCards) {
    int rankPresent[13] = {0};
    for(int i=0; i<numCards; i++){
	rankPresent[cards[i].rank] = 1;
    }
	
    int conCount = 0;
    for(int i=0; i<13 ; i++){
	if(rankPresent[i]){
		conCount++;
		if(conCount == 5){
			return true;
		}
	}
	else{
		conCount=0;
	}
    }

    if(rankPresent[ACE] && rankPresent[TWO] && rankPresent[THREE] && rankPresent[FOUR] && rankPresent[FIVE]){
	return true;
    }

	return false;
			
}

bool isFlush(Card *cards, int numCards){
    int clubs = 0;
    int diamonds = 0;
    int hearts = 0;
    int spades = 0;
    for(int i=0; i<numCards; i++){
        if(cards[i].suit == CLUBS){
            clubs++;
        }
        else if(cards[i].suit == DIAMONDS){
            diamonds++;
        }
        else if(cards[i].suit == HEARTS){
            hearts++;
        }
        else{
            spades++;
        }
    }
    if(spades>=5 || hearts>=5 || diamonds>=5 || clubs>=5){
        return true;
    }
    else{
        return false;
    }
}



int isRoyalFlush(Card *cards, int numCards) {
    if (cards[0].rank == TEN && cards[1].rank == JACK &&
        cards[2].rank == QUEEN && cards[3].rank == KING &&
        cards[4].rank == ACE) {
        for (int i = 1; i < numCards; i++) {
            if (cards[i].suit != cards[0].suit) {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

int isStraightFlush(Card *cards, int numCards) {
    for (int i = 1; i < numCards; i++) {
        if (cards[i].suit != cards[0].suit) {
            return 0;
        }
    }
    return isStraight(cards, numCards);
}

int checkStraightOrRoyalFlush(Card *cards, int numCards) {
    Card hand[5];
    int ans = 0;
    for (int i = 0; i < numCards - 4; i++) {
        for (int j = i + 1; j < numCards - 3; j++) {
            for (int k = j + 1; k < numCards - 2; k++) {
                for (int l = k + 1; l < numCards - 1; l++) {
                    for (int m = l + 1; m < numCards; m++) {
                        hand[0] = cards[i];
                        hand[1] = cards[j];
                        hand[2] = cards[k];
                        hand[3] = cards[l];
                        hand[4] = cards[m];
                        qsort(hand, 5, sizeof(Card), compareCards);
                        if (isRoyalFlush(hand, 5)) {
                            ans = 2;
                        } else if (isStraightFlush(hand, 5)) {
                            ans = 1 ;
                        }
                    }
                }
            }
        }
    }
    return ans;
}
