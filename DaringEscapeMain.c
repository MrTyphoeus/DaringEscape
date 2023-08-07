

//						        								DARING ESCAPE
// 
//																MADE BY FURKAN KESICIOGLU


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>														//Used libraries
#include <time.h>
#include <locale.h>
#include <conio.h>       
#include <windows.h> 

#define MAP_ROWS 5
#define MAP_COLS 15


enum MapElement {
	EMPTY = ' ',
	MINE = 'x',
	BONUS = '*',
	CHARACTER = 4
};

char map[MAP_ROWS][MAP_COLS];
char playmap[MAP_ROWS][MAP_COLS];

//Map functions START

void make_Map(char map[MAP_ROWS][MAP_COLS]) {					   //Function for making random matrix map

	srand(time(NULL));									        	//For random number.

	for (int i = 0; i < MAP_ROWS; i++) {
		for (int j = 0; j < MAP_COLS; j++) {
			map[i][j] = EMPTY;										//First place empty
			int randomNumber = rand() % 3;							//Choses randomly 0 or 1 
			if (randomNumber == 1)							   	    //If random number equals to 1, places x to that coordinate 
				map[i][j] = MINE;
			randomNumber = rand() % 10;
			if (randomNumber == 1)							   	    //If random number equals to 1, places x to that coordinate 
				map[i][j] = BONUS;

		}
	}


}

void copy_Map(char map[MAP_ROWS][MAP_COLS], char playmap[MAP_ROWS][MAP_COLS]) {  //Function for copying the map
	for (int i = 0; i < MAP_ROWS; i++) {
		for (int j = 0; j < MAP_COLS; j++) {
			playmap[i][j] = map[i][j];
		}
	}
}

//Map functions END





//Printing functions START

void print_Map(char map[MAP_ROWS][MAP_COLS]) {										//Function for printing map
	system("cls");
	for (int i = 0; i < MAP_ROWS; i++) {
		for (int j = 0; j < MAP_COLS; j++) {
			printf("  %c  ", map[i][j]);
		}
		printf("|");
		printf("\n\n");
	}

}

void print_Start() {                                       //Start message
	printf("\n\n\t\tWelcome to the Daring Escape!!\n\n\n\t\tThe purpose of the game is reaching to the end by going through less % c and move number.\n\n\t\tFor bonus go through % c \n\n\n\n", MINE, BONUS);
	system("pause");
}

void print_Ingame(int moveNumber, int score, int currentPlayer) {							//Ingame controls; number and score print
	printf("\n\t\t ^ \n\t\t(W)\n\n\t<-(A)\t      (D)->\t\t\t\tPLAYER %d\n\n\t\t(S)\n\t\t V\n\n", currentPlayer);
	printf("\nNumber Of Moves: %d\t\t\t", moveNumber);
	printf("Score: %d\n", score);
}

void print_Menu(int* selected, int* mapCounter, int* currentPlayer) {


	while (*selected == 1) {							     	 // 49 for 1, 50 for 2, 51 for 3 (ASCII)
		*selected = _getch();
		switch (*selected) {
		case 49:						 // Different map
			(*mapCounter)++;
			make_Map(map);
			*currentPlayer = 1;
			break;
		case 50:						// Same map
		case 51:						// Quit
			break;
		default:
			*selected = 1;
			break;
		}
	}

}


void print_End(int mapCounter, int currentPlayer, int moveNumber, int score, int score1, int score2) {	//Print after lap message

	system("cls");

	printf("\n\n\n\t\t\tSuccessfully completed !\t\t\t Map:%d \n\n", mapCounter);
	printf("\t\t\tNumber of moves: %d \t\t\t\n", moveNumber);



	printf("\t\t\t\t\t\t\t\t\tPlayer 1: %d\n", score1);
	printf("\t\t\t\t\t\t\t\t\tPlayer 2: %d\n", score2);

	printf("\n\t\t\tScore: %d \t\t\t\n\n\n", score);
	printf("\t\t\tFor different map (1)\n\t\t\tWith same map (2)\n\t\t\tTo quit (3)\n");


}

//Printing functions END




//Character mover function
int move_Character(char map[MAP_ROWS][MAP_COLS], int* currentRow, int* currentColumn, int* score, int* moveNumber, int* oldValue) {

	map[*currentRow][*currentColumn] = *oldValue;

	char wasdCoordinateChange = _getch();

	switch (wasdCoordinateChange) {
	case 'd':
	case 'D':
		(*currentColumn)++;
		break;
	case 'a':
	case 'A':
		(*currentColumn)--;
		break;
	case 's':
	case 'S':
		(*currentRow)++;
		break;
	case 'w':
	case 'W':
		(*currentRow)--;
		break;
	default:
		printf("Please enter a valid value\n");
		map[*currentRow][*currentColumn] = CHARACTER;
		Sleep(200);
		return 0;
	}


	//Handle Map Borders 

	if (*currentColumn >= MAP_COLS)
		return 0;

	if (*currentRow < 0 || *currentRow > 4) {						//If it goes on top of the map, it throws it under. If it comes out from under the map, it throws it on top of it.
		*currentRow = (*currentRow < 0) ? MAP_ROWS - 1 : 0;					//If row number is less than 0 that means CHARACTER went over the map sets new value to the bottom.
		//If isnt less than zero, its more than MAP_ROWS-1 this means CHARACTER went under the map sets new value to the top.	
	}

	*currentColumn = (*currentColumn < 0) ? 0 : *currentColumn;

	//Handle Map Borders end

	*oldValue = map[*currentRow][*currentColumn];

	if (map[*currentRow][*currentColumn] == BONUS) {
		*score += 5;
		*oldValue = EMPTY;
	}

	map[*currentRow][*currentColumn] = CHARACTER;


	if (*oldValue == 'x')									//If CHARACTER pressed to mine, lower the score by 5.
		*score -= 5;

	*moveNumber += 1;
	*score -= 1;


}


//Player score selecter function
int current_Player(int* currentPlayer, int score, int* score1, int* score2) {

	switch (*currentPlayer) {

	case 1: *score1 = score;
		*currentPlayer = 2;
		break;

	case 2: *score2 = score;		
		*currentPlayer = 1;
		break;

	default:
		return 0;
	}

}

void main() {

	print_Start();
	make_Map(map);


	int selected = 1, mapCounter = 1, currentPlayer = 1, score1 = 0, score2 = 0;

	while (selected != 51) {


		int currentRow = 2, currentColumn = 0, score = 100, moveNumber = 0, oldValue = 0;


		selected = 1;                                                   //Selected reset.

		oldValue = map[0][2];											//Sets the oldValue's value where CHARACTER will begin.
		map[2][0] = CHARACTER;											//Put CHARACTER in to the left center of the map.

		copy_Map(map, playmap);											//With this; even we make change ingame map source will stay the same 

		while (currentColumn < MAP_COLS && currentColumn >= 0) {				//Continues as long as the character does not finish the map

			print_Map(playmap);

			print_Ingame(moveNumber, score, currentPlayer);

			move_Character(playmap, &currentRow, &currentColumn, &score, &moveNumber, &oldValue);

		}
		current_Player(&currentPlayer, score, &score1, &score2);

		print_End(mapCounter, &currentPlayer, moveNumber, score, score1, score2);

		print_Menu(&selected, &mapCounter, &currentPlayer);

	}
}
