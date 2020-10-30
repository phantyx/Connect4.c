#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int Initialization();
int Teardown();
char AcceptInput(char player[]);
int UpdateWorld(char input);
int DisplayWorld(int switchResult);
char player1[20]; 		// Player 1 Name
char player2[20]; 		// Player 2 Name
char currentSymbol; 		// Holds the current symbol to be placed
bool GameContinue = true; 	// Flag for the game loop
int flipflop = 0; 		// Tracks which player is taking their turn
int boardRows = 6; 		// Board Height
int boardColumns = 7; 		// Board Width
char** board; 			// Board Pointer
int aCount = 0; 		// Counts keeping track of how high each "stack" is for each row.
int bCount = 0; 		// 		I approached it this way rather than iterating through each
int cCount = 0; 		// 		column in the grid to check it's current size.
int dCount = 0;
int eCount = 0;
int fCount = 0;
int gCount = 0;

int main ()
{
	Initialization();
	DisplayWorld(0);
	while (GameContinue == true) 		// Game loop. Manipulates currentSymbol to match the respective player.
	{
		if ((flipflop % 2) == 0){
			currentSymbol = 'x';
			DisplayWorld(UpdateWorld(AcceptInput(player1)));
		} else {
			currentSymbol = 'o';
			DisplayWorld(UpdateWorld(AcceptInput(player2)));
		}
		flipflop++;
	}
	Teardown();
	return 0;
}

int Initialization () 		// Creates the game board and takes inputs for player names.
{
	char toggle = 'n';
	printf("Setting up the game...\n");
	board = (char **)malloc(boardColumns * sizeof(char *)); 	// Makes an array of size 7
	for (int i = 0; i < boardColumns; i++)				// Iterates through, 7 times
		board[i] = (char *)malloc(boardRows * sizeof(char));	// Makes arrays of size 6 and adds them to each address (0-6)
	for (int j = 0; j < boardColumns; j++)				// Then fills each address with a '_' to denote an empty slot.
	{
		for (int k = 0; k < boardRows; k++)
			board[j][k] = '_';
	}
	printf("Setup Completed.\n");
	while (toggle == 'n')
	{
		printf("Player 1 - Enter Name: ");	
		scanf("%s", player1);
		printf("Player 2 - Enter Name: ");
		scanf("%s", player2);
		printf("Player 1 (x's): %s | Player 2 (o's): %s\n", player1, player2);
		printf("(y/n) Is this correct? : ");					
		scanf(" %c", &toggle);									// Checks for name correctness, allows the user to input new names if incorrect.
		if (toggle == 'y')									// Simple y/n with input validation.
		{
			break;
		}
		else if (toggle != 'n') 
		{
			printf("Not a valid input, try again: ");
			scanf(" %c", &toggle);
		}
	}
	return 0;
}

int Teardown()			// Iterates through the sub-arrays, freeing them, then frees the initial array.
{
	printf("Destroying the game...\n");
	for (int i = 0; i < boardRows; i++)
		free(board[i]);
	free(board);
	printf("Destruction Completed.\n");
	return 0;
}

char AcceptInput(char *player)		// Handles user input with validation. 
{
	char input;
	printf("(q to quit) %s's Move (%c's): ", player, currentSymbol);
	scanf(" %c", &input);
	while (&input != NULL)
	{
		if (input == 'a' || input == 'b' || input == 'c' || input == 'd' || input == 'e' || input == 'f' || input == 'g' || input == 'q')
			return input;
		else
		{
			printf("Not a valid input, try again: ");
			scanf(" %c", &input);
		}
	}
}

int UpdateWorld(char input)			// Handles validated inputs. Switch case for each column and sends game-ending cases to DisplayWorld.
{
	switch(input)
	{
		case 'a' :					// Each column's respective switch case.
		{
			if (aCount < 6)
			{
				board[0][aCount] = currentSymbol;
				aCount++;
				break;
			}
			else
				return 2;
		}
		case 'b' :
		{
			if (bCount < 6)
			{
				board[1][bCount] = currentSymbol;
				bCount++;
				break;
			}
			else
				return 2;
		}
		case 'c' :
		{
			if (cCount < 6)
			{
				board[2][cCount] = currentSymbol;
				cCount++;
				break;
			}
			else
				return 2;
		}
		case 'd' :
		{
			if (dCount < 6)
			{
				board[3][dCount] = currentSymbol;
				dCount++;
				break;
			}
			else
				return 2;
		}
		case 'e' :
		{
			if (eCount < 6)
			{
				board[4][eCount] = currentSymbol;
				eCount++;
				break;
			}
			else
				return 2;
		}
		case 'f' :
		{
			if (fCount < 6)
			{
				board[5][fCount] = currentSymbol;
				fCount++;
				break;
			}
			else
				return 2;
		}
		case 'g' :
		{
			if (gCount < 6)
			{
				board[6][gCount] = currentSymbol;
				gCount++;
				break;
			}
			else
				return 2;
		}
		case 'q' :					// Force quit switch case.
			return 3;
	}

	if (flipflop > 5) // Win Condition Checks, sent to DisplayWorld.
	{
		for (int i = 0; i < boardRows; i++) // Horizontal Win Condition Check
		{
			for (int j = 0; j < 4; j++)
			{
				if (board[j][i] == board[j+1][i] && board[j][i] == board[j+2][i] && board[j][i] == board[j+3][i] && board[j][i] != '_')
					return 1;
			}
		}

		for (int i = 0; i < boardColumns; i++) // Vertical Win Condition Check
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[i][j] == board[i][j+1] && board[i][j] == board[i][j+2] && board[i][j] == board[i][j+3] && board[i][j] != '_')
					return 1;
			}
		}

		for (int i = 0; i < 4; i++) // Diagonal Forward (/) Win Condition Check
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[i][j] == board[i+1][j+1] && board[i][j] == board[i+2][j+2] && board[i][j] == board[i+3][j+3] && board[i][j] != '_')
					return 1;
			}
		}

		for (int i = 6; i > 2; i--) // Diagonal Backward (\) Win Condition Check
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[i][j] == board[i-1][j+1] && board[i][j] == board[i-2][j+2] && board[i][j] == board[i-3][j+3] && board[i][j] != '_')
					return 1;
			}
		}
	}
	return 0;
}

int DisplayWorld(int switchResult)			// Phyiscally prints the board. 
{
	switch (switchResult)
	{
		//*
		case 1 :				// Case 1: Someone won the game by connecting 4 discs. 
		{
			for (int i = 0; i < boardRows; i++)
			{
				printf("|");
				for (int j = 0; j < boardColumns; j++)
				{
					printf("%c|", board[j][boardRows - 1 - i]);
				}
				printf("\n");
			}
			printf("---------------\n|a|b|c|d|e|f|g|\n");
			if (currentSymbol == 'x')
				printf("%s wins!\n", player1);
			else
				printf("%s wins!\n", player2);
			GameContinue = false;
			break;
		} 
		
		case 2 :				// Case 2: An already-full column was attempted as an
		{
			for (int i = 0; i < boardRows; i++)
			{
				printf("|");
				for (int j = 0; j < boardColumns; j++)
				{
					printf("%c|", board[j][boardRows - 1 - i]);
				}
				printf("\n");
			}
			printf("---------------\n|a|b|c|d|e|f|g|\n");
			printf("That column is full. Game over.\n");
			GameContinue = false;
			break;
		}
		case 3 :				// Case 3: The force-quit input was recieved. 
		{
			for (int i = 0; i < boardRows; i++)
			{
				printf("|");
				for (int j = 0; j < boardColumns; j++)
				{
					printf("%c|", board[j][boardRows - 1 - i]);
				}
				printf("\n");
			}
			printf("---------------\n|a|b|c|d|e|f|g|\n");
			printf("The game has been quit.\n");
			GameContinue = false;
			break;
		}
		default :				// Default: Default simply prints the updated board.
		{ 
			for (int i = 0; i < boardRows; i++)
			{
				printf("|");
				for (int j = 0; j < boardColumns; j++)
				{
					printf("%c|", board[j][boardRows - 1 - i]);
				}
				printf("\n");
			}
			printf("---------------\n|a|b|c|d|e|f|g|\n");
		}
	}

	return 0;
	
}
