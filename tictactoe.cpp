// libs
#include <cstdio>
#include <cstdlib>

// clear console command
#ifdef _WIN32
#define CLEAR "cls"
#else //In unix/linux
#define CLEAR "clear"
#endif

// Print game board with scores
void printBoard( char* game, int* player1Score, int* player2Score, char* winPtn ) {
	printf("\n+-----------------------------------------------------+\n");
        printf("|     %c %c   |   %c   |   %c %c                           |\n", winPtn[6], winPtn[3], winPtn[4], winPtn[5], winPtn[7]);
        printf("|     %c %c %c | %c %c %c | %c %c %c     *******************   |\n",winPtn[0], game[2], winPtn[0], winPtn[0], game[1], winPtn[0], winPtn[0], game[0], winPtn[0]);
        printf("|       %c %c |   %c   | %c %c       *                 *   |\n", winPtn[3], winPtn[6], winPtn[4], winPtn[7], winPtn[5] );
        printf("|    -------+-------+-------    * Player 'X': %3d *   |\n", *player1Score);
        printf("|       %c   | %c %c %c |   %c       *                 *   |\n", winPtn[3], winPtn[6], winPtn[4], winPtn[7], winPtn[5]);
        printf("|     %c %c %c | %c %c %c | %c %c %c     *******************   |\n", winPtn[1], game[5], winPtn[1], winPtn[1], game[4], winPtn[1], winPtn[1], game[3], winPtn[1]);
        printf("|       %c   | %c %c %c |   %c       *                 *   |\n", winPtn[3], winPtn[7], winPtn[4], winPtn[6], winPtn[5]);
        printf("|    -------+-------+-------    * Player 'O': %3d *   |\n", *player2Score);
        printf("|       %c %c |   %c   | %c %c       *                 *   |\n", winPtn[3], winPtn[7], winPtn[4], winPtn[6], winPtn[5]);
        printf("|     %c %c %c | %c %c %c | %c %c %c     *******************   |\n",winPtn[2], game[8], winPtn[2], winPtn[2], game[7], winPtn[2], winPtn[2], game[6], winPtn[2]);
        printf("|     %c %c   |   %c   |   %c %c                           |\n", winPtn[7], winPtn[3], winPtn[4], winPtn[5], winPtn[6]);
	printf("+-----------------------------------------------------+\n\n");
}

// clear Console screen. Get better way for this since system function is OS dependent :/
void clearConsole()
{
	system(CLEAR); // The ugly evil thing xD
}

// Get only first inserted char from terminal
char getInputChar()
{
	char input = '\n';
	char c = '\n';
	bool caughtChar = false;
	bool tooManyCharError = false;
	// Clear the input buffer
        while ((c = getchar()) != '\n' && c != EOF)
	{
		if( !caughtChar )
		{
			input = c;
			caughtChar = true;
		}
		else
			if( !tooManyCharError )
			{
				printf("*** Too many arguments, please insert only one  ***\n");
				tooManyCharError = true;
 				input = '\n';
			}
	}
	return input;
}

// Game core
int main() {

    // Game variables
    bool exit = false;
    bool gameEnd = false;
    char game[9];
    int player1Score = 0;
    int player2Score = 0;
    int play;
    char turn;
    int position;
    char positionInput;
    char exitInput;
    char winPtn[8];

    //Game start
    while( !exit )
    {
	// Set start settings
	clearConsole();
	play = 0;
	position = -1;
	positionInput = 0;
	exitInput = 0;
	turn = 'X';
	printf("*******************************************************\n");
	printf("*          Hello World, Welcome to TicTacToe          *\n");
	printf("*******************************************************\n");

	// Print game board positions
        for(int i = 0; i < 9; i++)
        {
            game[i] = 57 - i;
        }

	for( int i = 0; i < 8; i++ )
	{
	    winPtn[i] = ' ';
	}

        printBoard( game, &player1Score, &player2Score, winPtn );

	// Clear game table
	for(int i = 0; i < 9; i++ )
	{
		game[i] = ' ';
	}

	printf("--> Press <Enter> key to start <--\n");
	getInputChar();

	// Game loop
	while( !gameEnd )
	{
		clearConsole();
		play++;
		printf("*******************************************************\n");
		printf("*                    Play Nº %d                        *\n", play);
		printf("*******************************************************\n");
		printBoard( game, &player1Score, &player2Score, winPtn );
		printf("--> It's time for '%c' play, what position is desired? [1 - 9] <--\n", turn);
		// Loop until valid input is made
		while( position < 0 || position > 8 )
		{
			positionInput = getInputChar();
			position = 57 - positionInput;
			if( game[position] != ' ' || positionInput < 48 || positionInput > 57 )
			{
				if( positionInput != '\n' )
					printf("*** Position %c not available, please play again ***\n", positionInput);
				position = -1;
				positionInput = 0;
			}
		}
		game[position] = turn;

		position = -1;

		//Check if there is winner for current turn
		if( play > 4 )
		{
			if( game[0] == turn && game[1] == turn && game[2] == turn )
				winPtn[0] = '*';
			if( game[3] == turn && game[4] == turn && game[5] == turn )
				winPtn[1] = '*';
			if( game[6] == turn && game[7] == turn && game[8] == turn )
				winPtn[2] = '*';
			if( game[2] == turn && game[5] == turn && game[8] == turn )
				winPtn[3] = '*';
			if( game[1] == turn && game[4] == turn && game[7] == turn )
				winPtn[4] = '*';
			if( game[0] == turn && game[3] == turn && game[6] == turn )
				winPtn[5] = '*';
			if( game[0] == turn && game[4] == turn && game[8] == turn )
				winPtn[7] = '*';
			if( game[2] == turn && game[4] == turn && game[6] == turn )
				winPtn[6] = '*';

			for(int i = 0; i < 8; i++)
			{
				if( winPtn[i] == '*' )
				{
					clearConsole();
					gameEnd = true;
					printf("*******************************************************\n");
					printf("*               Player %c won the match                *\n", turn);
					printf("*******************************************************\n");
					if( turn == 'X' )
						player1Score ++;
					else
						player2Score++;
				        printBoard( game, &player1Score, &player2Score, winPtn );
					break;
				}
			}
		}

		if( !gameEnd )
		{
			if( turn == 'X' )
				turn = 'O';
			else
				turn = 'X';
			if( play == 9 )
			{
				clearConsole();
				printf("*******************************************************\n");
				printf("*             The match ended with a draw             *\n");
				printf("*******************************************************\n");
			        printBoard( game, &player1Score, &player2Score, winPtn );
				gameEnd = true;
			}
		}
	}

	//Exit dialog
	printf("--> Want to play again [Y, N]? <--\n");

	gameEnd = false;

	// Loop until valid input
	while( exitInput != 89 && exitInput != 121 && exitInput != 78 && exitInput != 110 )
	{
		exitInput = getInputChar();
		if( exitInput == 78 || exitInput == 110 )
			exit = true;
		if( exitInput != 89 && exitInput != 121 && exitInput != 78 && exitInput != 110 && exitInput != '\n' )
		{
			printf("*** Invalid command inserted, please answer [Y, N] ***\n");
			exitInput = 0;
		}
	}
    }

    return 0;
}
