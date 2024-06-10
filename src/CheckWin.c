
#include<Structures.h>

void checkHands(struct Player playersList[10], struct Card boardCards[5])
{
    // This function should evaluate the hands and set the hand type for each player.
    // For simplicity, we'll assume all players have HighCard.
    for (int i = 0; i < 10; i++)
    {
        if (playersList[i].status == 1)
        {
            playersList[i].hand = HighCard; // Placeholder logic
        }
    }

    Card checkBoard[7];
    for (int i = 0; i < 5; i++)
    {
        checkBoard[i] = boardCards[i];
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 5; j < 7; j++)
        {
            checkBoard[j] = playerList[i]->handCards[j - 5];
        }

        // Fisrt check for royal flush

        // Second check for Straight FLush
        if (isFlush(checkBoard) && isStraight(checkBoard))
        {
            // Add more logic since some card can form a flush while others may form a straight
            playerList[i]->hand = StraightFlush;
            continue;
        }
        // Third check for Four of a Kind

        // Fifth check for Flush
        if (isFlush(checkboard))
        {
            playerList[i].hand->Flush;
            continue;
        }
        // Sixth check for Straight
        if (isStraight(checkboard))
        {
            playerList[i].hand->Straight;
            continue;
        }
        // Seventh check for Three of A Kind

        // Eight check for Two Pair

        // Ninth check for One Pair

        // Tenth check for high card
        playerList[i].hand->HighCard
    }
}

void checkWinner(struct Player playersList[10])
{
    int winnerIndex = 0;
    for (int i = 1; i < 10; i++)
    {
        if (playersList[i].status == 1 && playersList[i].hand > playersList[winnerIndex].hand)
        {
            winnerIndex = i;
        }
        else if (playersList[1].status == 1 && playersList[i].hand == playersList[winnerIndex].hand)
        {
            // we have to check who has the higher card
            // also check if all the cards on the board are higher
        }
    }
    printf("Winner is %s with %d points.\n", playersList[winnerIndex].name, playersList[winnerIndex].points);
}

bool isFlush(struct Card checkBoard[7])
{
    int clubs, diamonds, hearts, spades = 0, 0, 0, 0;
    for (int i = 0; i < 7; i++)
    {
        if (checkBoard[i]->suit == CLUBS)
        {
            clubs++;
        }
        else if (checkBoard[i]->suit == DIAMONDS)
        {
            diamonds++;
        }
        else if (checkBoard[i]->suit == HEARTS)
        {
            hearts++;
        }
        else
        {
            spades++;
        }
    }
    if (spades >= 5 || hearts >= 5 || diamonds >= 5 || clubs >= 5)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isStraight(struct Card checkBoard[7])
{
    struct Card tempBoard[7];
    for (int i = 0; i < 7; i++)
    {
        tempBoard[i] = checkBoard[i];
    }
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6 - i; j++)
        {
            if (tempBoard[j]->rank > tempBoard[j + 1]->rank)
            {
                struct Card temp = tempBoard[j];
                tempBoard[j] = tempBoard[j + 1];
                tempBoard[j + 1] = temp;
            }
        }
    }
    // Array to mark the presence of each rank
    int rankPresent[RANK_COUNT] = {0};

    // Mark the presence of each rank in the sorted array
    for (int i = 0; i < 7; i++)
    {
        rankPresent[tempBoard[i].rank] = 1;
    }

    // Check for 5 consecutive ranks
    int consecutiveCount = 0;
    for (int i = 0; i < RANK_COUNT; i++)
    {
        if (rankPresent[i])
        {
            consecutiveCount++;
            if (consecutiveCount == 5)
            {
                return true;
            }
        }
        else
        {
            consecutiveCount = 0;
        }
    }

    // Special case for Ace-low straight (A-2-3-4-5)
    if (rankPresent[ACE] && rankPresent[TWO] && rankPresent[THREE] && rankPresent[FOUR] && rankPresent[FIVE])
    {
        return true;
    }

    return false;
}
