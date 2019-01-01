#include "GameState.h"

int main()
{
	GameState game;
	int row, column;

	while ( game.continuing() ) {
		game.display();
		std::cout << "Input your row/column (ex: 3 1): ";
		std::cin >> row;
		std::cin >> column;

		std::cout << "Row: " << row << " Column: " << column << std::endl;
	}

	return 0;
}