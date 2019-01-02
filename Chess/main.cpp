#include "GameState.h"

int main()
{
	GameState game;
	int startRow, startColumn, endRow, endColumn;

	while ( game.continuing() ) {
		game.display();
		std::cout << "Input your start & end row/column (ex: 3 1 5 6): ";
		std::cin >> startRow;
		std::cin >> startColumn;
		std::cin >> endRow;
		std::cin >> endColumn;

		if (game.validateMove(startRow, startColumn, endRow, endColumn))
		{
			game.displayMove(startRow, startColumn, endRow, endColumn);
			game.movement(startRow, startColumn, endRow, endColumn);
		}
		
		else
		{
			std::cout << "Invalid Input... Please try again" << std::endl;
		}
	}


	return 0;
}