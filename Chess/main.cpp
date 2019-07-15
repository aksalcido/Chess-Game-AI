#include "GameState.h"

int main()
{
	// Initializes a GameState of the Chess Game
	Chess::GameState game;

	// Initializes the variables to store user input
	int startRow, startColumn, endRow, endColumn;

	// Displays the Board to the User
	game.display();

	while ( game.continuing() ) {
		// Prompts the User and proceeds to take input
		game.prompt("Input your start & end row/column (ex: 3 1 5 6): ");
		game.input(startRow, startColumn, endRow, endColumn);

		// Game Checks if the move inputted from the user is valid, if so proceeds to progress the game
		if (game.validateMove(startRow, startColumn, endRow, endColumn))
		{
			game.displayMove(startRow, startColumn, endRow, endColumn);
			game.progress(startRow, startColumn, endRow, endColumn);
			game.display();
		}
		// Otherwise informs the user that the move is invalid
		else
		{
			game.prompt("Invalid Move... Please try again\n");
		}

		// Invalid Input that causes input stream to fail is handled here
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	std::cout << "Game is complete" << std::endl;

	return 0;
}