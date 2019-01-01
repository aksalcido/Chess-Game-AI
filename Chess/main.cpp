#include "GameState.h"

int main()
{
	GameState game;
	int rowStart, columnStart, rowEnd, columnEnd;

	while ( game.continuing() ) {
		game.display();
		std::cout << "Input your start & end row/column (ex: 3 1 5 6): ";
		std::cin >> rowStart;
		std::cin >> columnStart;
		std::cin >> rowEnd;
		std::cin >> columnEnd;

		if (game.validateMove(rowStart, columnStart, rowEnd, columnEnd))
		{
			std::cout << "Move: (" << rowStart << ", " << columnStart << ") -> (" << rowEnd << ", " << columnEnd << ")" << std::endl;
			
		}
		
		else
		{
			std::cout << "Invalid Input... Please try again" << std::endl;
		}
	}


	return 0;
}