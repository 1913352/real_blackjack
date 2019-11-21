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


//playing game functions -----------------------------


//get an integer input from standard input (keyboard)
//return : input integer value
//         (-1 is returned if keyboard input was not integer)
int getIntegerInput(void) {
    int input, num;
    
    num = scanf("%d", &input);
    fflush(stdin);
    if (num != 1) //if it fails to get integer
        input = -1;
    
    return input;
}

//player settiing
int configUser(void) {
	do
	{
		printf("Input the number of users (Max:5) :");
		scanf("%d", &n_user);
	
		if (n_user>5)
			printf("Too many players!\n");
		
		else if (n_user<1)
			printf("invalid input players\n");
	
		} while (n_user>5 || n_user<1);
		
		printf(" --> card is mixed and put into the tray\n\n");
		printf("------------------------------------------------\n------------ ROUND 1 (cardIndex:0)--------------------------\n------------------------------------------------\n\n");
		
}


//betting
int betDollar(void) {
	int bet_dollar;
	int i;
	int bet[4];
	
	printf("------- BETTING STEP -------\n");

	do{
		printf("  -> your betting (total:$50) : ");
		scanf("%d", &bet_dollar);// input your betting dollars
	
		if (bet_dollar>50)
			printf("   -> you only have $50! bet again\n");
		else if (bet_dollar<1)
			printf("   -> invalid input for betting\n");
	}while (bet_dollar<50 && bet_dollar>1);

	for (i=1;i<n_user;i++)
	{
		bet[i]=(rand()%N_MAX_BET)+1;
		printf("   -> player[%d] bets %d (out of $50)\n", i, bet[i]); // player's dollar is random
	
	printf("----------------------------\n\n");
}
}

//offering initial 2 cards
void offerCards(void) {
	int i;
	//1. give two card for each players
	for (i=0;i<n_user;i++)
	{
		cardhold[i][0] = pullCard();
		cardhold[i][1] = pullCard();
	}
	//2. give two card for the operator
	cardhold[n_user][0] = pullCard();
	cardhold[n_user][1] = pullCard();
	
	return;
}

//print initial card status
void printCardInitialStatus(void) {
	int i;
	
	printf(" ----------- CARD OFFERING ---------------\n");
	
	//server card
	printf(" --- server      : X ");
	printfCard(cardhold[n_user][1]);
	printf("\n");
	
	//your card
	printf("   -> you        :  ");
	printCard(cardhold[0][0]);
	printCard(cardhold[0][1]);
	printf("\n"); 
	
	//player card
	for (i=1;i<n_user;i++)
		printf("   -> player  %d  : ", i);
		printCard(cardhold[i][0]);
		printCard(cardhold[i][1]);
		printf("\n");
}




void printUserCardStatus(int user) {
	int i;
	int cardcnt;
	
	if (user ==0)
		printf("your card :");
	else if (user ==n_user)
		printf("server card :");
	else
		printf("player %d card :", user);
		
	printf("   -> card : ");

	for (i=0;i<cardcnt;i++)
		printCard(cardhold[user][i]);
	printf("\t ::: ");
}

	
//my action 
int get_myAction(int i) {

	char action[5];    // go or stay 
	printf("::: Action? (0 - go, others - stay) :");
	scanf("%d", &action);
	
	if (action[0]==0)
		return 1;
		
	else
		return 0;                                 
	
	}

	
//players and dealer action
int get_userAction(int user){
	if (cardSum[user]<17)
		return 1;
		
	else
		return 0;
}



