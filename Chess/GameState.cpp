#include "GameState.h"

GameState::GameState() : turn(white), GameOver(false)
{

}

void GameState::movement(int row, int col, int endRow, int endCol)
{
	if (ChessBoard.emptySpace(endRow, endCol))
	{
		ChessBoard.movementToEmptySquare(row, col, endRow, endCol);
	}
	else
	{
		ChessBoard.movementToEnemy(row, col, endRow, endCol);
	}

	ChessBoard.firstMoveCheck(endRow, endCol);
	ChessBoard.updateCoordinates(endRow, endCol);

}

bool GameState::validateMove(int row, int col, int endRow, int endCol)
{
	// Within Boundaries of the Board for Start/End Coordinates
	if (ChessBoard.inBounds(row, col) && ChessBoard.inBounds(endRow, endCol)) {

		// Start Position must be a GameObject
		if (!ChessBoard.emptySpace(row, col) && ChessBoard.pieceColor(row, col) == turn) {
			return ChessBoard.validMove(row, col, endRow, endCol);
		}
	}

	return false;
}

bool GameState::continuing() const
{
	return !GameOver;
}

void GameState::display() const
{
	std::cout << "   0 1 2 3 4 5 6 7\n -------------------" << std::endl;

	for (unsigned int i = 0; i < dimension; i++)
	{
		std::cout << i << "| ";

		for (unsigned int j = 0; j < dimension; j++) {
			if ( ! ChessBoard.emptySpace(i,j) )
				std::cout << ChessBoard.piece(i, j) << " ";
			else
				std::cout << ". ";
		}

		std::cout << "|" << std::endl;
	}

	std::cout << " -------------------" << std::endl;

	if ( continuing() )
		std::cout << "It is " << (turn == white ? "white's " : "black's ") << "turn to move!" << std::endl;
}

void GameState::displayMove(int startRow, int startColumn, int endRow, int endColumn)
{
	std::cout << "Move: (" << startRow << ", " << startColumn << ") -> (" << endRow << ", " << endColumn << ")" << std::endl;
}


GameState::~GameState()
{

}
