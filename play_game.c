#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50


#define N_MAX_CARDNUM		13
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10
#define N_MAX_GO			17
#define N_MAX_BET			5

#define N_MIN_ENDCARD		30


//card tray object
extern int CardTray[N_CARDSET*N_CARD];
int cardIndex = 0;							
int card_set[52] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51};
//0~12 heart, 13~25 dia, 26~38 spade, 39~51 club
int roundIndex = 0;
extern int cardcnt;

//player info
extern int dollar[N_MAX_USER];						//dollars that each player has
extern int n_user;									//number of users


//play yard information
extern int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
extern int cardSum[N_MAX_USER];					//sum of the cards
extern int bet[N_MAX_USER];						//current betting 
int gameEnd = 0; 							//game end flag

//some utility functions


int main(int argc, char *argv[]) {
	int roundIndex = 0;
	int max_user;
	int i;
	
	srand((unsigned)time(NULL));
	
	//set the number of players
	configUser();


	//Game initialization --------
	//1. players' dollar
	for (i=0;i<n_user;i++);
	{
		dollar[i] = N_DOLLAR;
	}
	
	//2. card tray
	mixCardTray();




	//Game start --------
	
		 


	do {
		cardSum[i] = calcStepResult();     //check the card status ::: calcStepResult()
		
		printf("------------------------------------------------\n------------ ROUND %d (cardIndex:%d)--------------------------\n------------------------------------------------", roundIndex, cardIndex);
		betDollar();
		offerCards(); //1. give cards to all the players
	
		printCardInitialStatus();
		printf("\n------------------ GAME start --------------------------\n");
	
		//my turn
		printf(">>> my turn! -------------\n");
		printUserCardStatus(0);
		
		if (cardSum[0] == 21)
			printf("BLACKJACK! (%d)", dollar[0]+2*bet[0]);
			
		else if (cardSum[0]>21)
			printf("lose (%d)", dollar[0]-bet[0]);
		
		else        //0<cardSum<21
		{
			get_myAction(0);
		
			if (gameEnd != 0)
			{
				break;
			}
		
		}
		
		printf("\n");
		
	

		//each player's turn
		for (i=1;i<n_user;i++) //each player
		{
			printf(">>> player %d turn! -------------\n", i);
			printUserCardStatus(i);      //print current card status printUserCardStatus();
			
			while (1) //do until the player dies or player says stop
			{
				printUserCardStatus(i);      //print current card status printUserCardStatus();
				
				if (calcStepResult(i) ==3)	             //check if the turn ends or not
				{
					printf("BLACKJACK!(%d)", dollar[i]+2*bet[i]);
					break;
				}
				
				else if (calcStepResult(i) ==2)
				{
					printf("lose (%d)", dollar[i]-bet[i]);
					break;
				}
				
				else if (cardSum[i]<17)
				{	get_userAction(i);      //GO? STOP? ::: getAction()
				
				}
				
				else if (cardSum[i]>17 && cardSum[i]<21)              // 17<cardSum<21
				{
					printf("  ::: STAY!\n");
				}
				
			
		}
		if ( gameEnd != 0)
		{
			break;
		}
		
		
			
		//dealer's turn
		printf(">>> server turn! ------------------------\n");
		printfUserCardStatus(n_user);
		
		if (cardSum[n_user]==21)
		{
			printf("BLACKJACK! All players lose");
			printf("[[[[[[[ server result is ....  21 ]]]]]]]");
		}
	
		else if (cardSum[n_user]>21)
		{
			printf("Server died. All players win");
			printf("[[[[[[[ server result is ....  overflow!! ]]]]]]]");
		}
	
		else if (cardSum[n_user]<17)
		{
			get_userAcion(n_user);
			printf("[[[[[[[ server result is ....  %d ]]]]]]]", cardSum[n_user]);
		}

		else              //17<cardSum<21
		{
				printf("  ::: STAY!\n");
				printf("[[[[[[[ server result is ....  %d ]]]]]]]", cardSum[n_user]);
		}
		}
		
		//result
		checkResult();
		
		printf(" \n\n-------------------- ROUND $d result ....\n", roundIndex);
		
		printf("   -> your result :   ");
		checkResult(0);
		
	
		for (i=1;i<n_user;i++)
		{
			printf("\n  -> 1'th player's result :  ");
			checkResult(i);
		}
		
		for (i=0;i<n_user;i++)
		{
			if (dollar[i]==0)
				gameEnd =1;
				
			else if (cardIndex>=48)
				gameEnd =1;
		}
		
		roundIndex++;
	
	} while (gameEnd == 0);
	
	checkWinner();
	
	
	return 0;
}


int calcStepResult(int user) {
	
	int i;

	cardSum[user] = 0;

	
// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
	if (cardSum[user]<21)
	{
		printf("%d", cardSum[user]);
		return 1;
	}
	
	else if (cardSum[user] >21)
	{
		printf("overflow");
		return 2;

	}
	
	else
	{
		printf("BLACKJACK!");
		return 3;
	}

		
	
	
	
}

int checkResult(int roundIndex) {
	
	int i;
	
	printf(" \n\n-------------------- ROUND $d result ....\n", roundIndex);
	
	for (i=0;i<n_user;i++)
	{	// your result
		if (i=0)
		{
			printf("   -> your result :   ");
			
			if (cardSum[0] = 21)
				printf("BLACKJACK! (%d)", dollar[i]+2*bet[i]);
				
			else if (cardSum[0]>21)
			{
				printf("Lose. overflow (%d)", dollar[i]-bet[i]);	
			}
			
			// dealer< you <21  -> win
			else if (cardSum[0]<21 && cardSum[0]>cardSum[n_user])
			{
				printf("win. (sum:%d) (%d)", cardSum[0], dollar[i]+bet[i]);
			}
			
			// you <21<dealer   -> win
			else if (cardSum[0]<21 && cardSum[n_user]>21)
			{
				printf("win. (sum:%d) (%d)", cardSum[0], dollar[i]+bet[i]);
			}
			
			// you < dealer <21  -> lose
			else if (cardSum[0]<cardSum[n_user] && cardSum[n_user]<21)
			{
				printf("lose. (sum:%d) (%d)", cardSum[0], dollar[i]-bet[i]);
			}
			
			// dealer=21, you!=21   ->lose
			else if (cardSum[n_user]=21 && cardSum[0]!=21)
			{
				printf("lose. (sum:%d) (%d)", cardSum[0], dollar[i]-bet[i]);
			}

		//player result
		else 
		{
			printf("\n  -> %d'th player's result :  ", i);
						if (cardSum[0] = 21)
				printf("BLACKJACK! (%d)", dollar[i]+2*bet[i]);
			
			//player>21   ->lose	
			else if (cardSum[i]>21)
			{
				printf("Lose. overflow (%d)", dollar[i]-bet[i]);	
			}
			
			// dealer< player <21  -> win
			else if (cardSum[i]<21 && cardSum[i]>cardSum[n_user])
			{
				printf("win. (sum:%d) (%d)", cardSum[i], dollar[i]+bet[i]);
			}
			
			// player <21<dealer   -> win
			else if (cardSum[i]<21 && cardSum[n_user]>21)
			{
				printf("win. (sum:%d) (%d)", cardSum[i], dollar[i]+bet[i]);
			}
			
			// player < dealer <21  -> lose
			else if (cardSum[i]<cardSum[n_user] && cardSum[n_user]<21)
			{
				printf("lose. (sum:%d) (%d)", cardSum[i], dollar[i]-bet[i]);
			}
			
			// dealer=21, player!=21   ->lose
			else if (cardSum[n_user]=21 && cardSum[i]!=21)
			{
				printf("lose. (sum:%d) (%d)", cardSum[i], dollar[i]-bet[i]);
			}
	
		}
	}
	
}
}

int checkWinner(void) {
	int i;
	int winner=0;
	
	for (i=0;i<n_user;i++)
	{
		if (dollar[i]>dollar[0])
		{	
			dollar[i]=dollar[0];
			winner=i;
		}	
	}
	
	if (i==0)
	{
		printf("\nwinner is you.");
	}
	
	else
	{
		printf("\n winner is %d player.", i);
	}
	
	
}

