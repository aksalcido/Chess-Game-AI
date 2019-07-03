#include "GameState.h"

Chess::GameState::GameState() : turn(white), GameOver(false)
{

}

void Chess::GameState::progress(int row, int col, int endRow, int endCol)
{
	movement(row, col, endRow, endCol);

	ChessBoard.castlingCheck(endRow, endCol);
	ChessBoard.firstMoveCheck(endRow, endCol);
	ChessBoard.updateCoordinates(endRow, endCol);
	ChessBoard.playerStatus(turn);

	nextTurn();
}

void Chess::GameState::movement(int row, int col, int endRow, int endCol)
{
	if (ChessBoard.emptySpace(endRow, endCol))
	{
		ChessBoard.movementToEmptySquare(row, col, endRow, endCol);
	}
	else
	{
		ChessBoard.movementToEnemy(row, col, endRow, endCol);
	}
}

void Chess::GameState::nextTurn()
{
	turn = (turn == white ? black : white);
}

bool Chess::GameState::validateMove(int row, int col, int endRow, int endCol)
{
	// Checks if the coordinates are on the board and if so whether the start coordinates are the player's piece
	if (playersMoveOnBoard(row, col, endRow, endCol) && isPlayersPiece(row, col)) {
		return ChessBoard.validMove(row, col, endRow, endCol);
	}

	return false;
}

bool Chess::GameState::continuing() const
{
	return !GameOver;
}

bool Chess::GameState::playersMoveOnBoard(int row, int col, int endRow, int endCol) const
{
	return ChessBoard.inBounds(row, col) && ChessBoard.inBounds(endRow, endCol);
}

bool Chess::GameState::isPlayersPiece(int row, int col) const
{
	return !ChessBoard.emptySpace(row, col) && ChessBoard.pieceColor(row, col) == turn;
}

void Chess::GameState::display() const
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

void Chess::GameState::displayMove(int startRow, int startColumn, int endRow, int endColumn) const
{
	std::cout << "Move: (" << startRow << ", " << startColumn << ") -> (" << endRow << ", " << endColumn << ")" << std::endl;
}


Chess::GameState::~GameState()
{

}
