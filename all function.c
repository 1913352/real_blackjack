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



//card processing functions ---------------



//calculate the actual card number in the blackjack game
int getCardNum(int cardnum) {
	
	if (cardnum%13 ==0)
		return 11;          // if (cardsum>21) -> return value -10  or cardsum -10
	
	if (cardnum%13 ==1)
		return 2;
		
	if (cardnum%13 ==2)
		return 3;
		
	if (cardnum%13 ==3)
		return 4;
		
	if (cardnum%13 ==4)
		return 5;
		
	if (cardnum%13 ==5)
		return 6;
		
	if (cardnum%13 ==6)
		return 7;
		
	if (cardnum%13 ==7)
		return 8;
		
	if (cardnum%13 ==8)
		return 9;
		
	if (cardnum%13 ==9)
		return 10;
		
	if (cardnum%13 ==10)
		return 10;

	if (cardnum%13 ==11)
		return 10;
		
	if (cardnum%13 ==12)
		return 10;
		
		
	
}

//print the card information (e.g. DiaA)
void printCard(int cardnum) {
	if (cardnum/13 ==0)        //0~12 heart
	{
		if (cardnum%13 ==0)
			printf("HRTA");
			
		else if (cardnum%13>0 && cardnum%13<10)
			printf("HRT%d", (cardnum+1)%13);
			
		else if (cardnum%13 ==10)
			printf("HRTJack");
			
		else if (cardnum%13 ==11)
			printf("HRTQueen");
			
		else 
			printf("HRTKing");
			
	}
	
	else if (cardnum/13 ==1)      //13~25 dia
	{
			if (cardnum%13 ==0)
			printf("DIAA");
			
		else if (cardnum%13>0 && cardnum%13<10)
			printf("DIA%d", (cardnum+1)%13);
			
		else if (cardnum%13 ==10)
			printf("DIAJack");
			
		else if (cardnum%13 ==11)
			printf("DIAQueen");
			
		else 
			printf("DIAKing");
	}
	
	else if (cardnum/13 ==2)        //26~38 spade
	{
		if (cardnum%13 ==0)
			printf("SPDA");
			
		else if (cardnum%13>0 && cardnum%13<10)
			printf("SPD%d", (cardnum+1)%13);
			
		else if (cardnum%13 ==10)
			printf("SPDJack");
			
		else if (cardnum%13 ==11)
			printf("SPDQueen");
			
		else 
			printf("SPDKing");
		
	}
	
	else             //39~51 club
	{
		if (cardnum%13 ==0)
			printf("CLVA");
		
		else if (cardnum%13>0 && cardnum%13<10)
			printf("CLV%d", (cardnum+1)%13);
			
		else if (cardnum%13 ==10)
			printf("CLVJack");
			
		else if (cardnum%13 ==11)
			printf("CLVQueen");
			
		else 
			printf("CLVKing");
	}
}



//card array controllers -------------------------------

//mix the card sets and put in the array
int mixCardTray(void) {
	int i;
	
	for (i=0;i<N_CARD;i++)
	{
		CardTray[i] = rand()%N_CARD;	}
}

//get one card from the tray
int pullCard(void) {
	cardIndex =0;
	cardIndex++;
	
	return CardTray[cardIndex-1];
}



