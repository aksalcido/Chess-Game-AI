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

	promotionCheck(endRow, endCol);
	ChessBoard.playerStatus();
	
	nextTurn();

	// Displays the Check to the User
	if (ChessBoard.kingInCheck(turn))
		displayCheck();

	// Checks for Gameover whether Checkmate or Stalemate -- expensive function
	try {
		ChessBoard.gameFinishedCheck(turn, ChessBoard.kingInCheck(turn));
	}

	catch (GameOverException e) {
		GameOver = true;
	}
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
		return ChessBoard.validMove(row, col, endRow, endCol) && ChessBoard.safeMove(row, col, endRow, endCol);
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

void Chess::GameState::displayCheck() const
{
	const char * player = (turn == white ? "White's " : "Black's ");
	std::cout << player << "king is in check!" << std::endl;
}

void Chess::GameState::displayWinner() const
{
	const char * winner;

	// Winner is the opposite player of the current turn
	if (ChessBoard.kingInCheck(turn))
	{
		winner = (turn == white ? "black!" : "white!");
		std::cout << "CHECKMATE! The winner of the match is " << winner << std::endl;
	}

	// STALEMATE !!!
	else {
		std::cout << "The Game has ended in a Stalemate!" << std::endl;
	}
}

void Chess::GameState::promotionCheck(int row, int col)
{
	// Pawn Promotion requires input on the Users part for what piece they want
	if (ChessBoard.promotion(row, col))
	{
		int userPromoted = displayPieceOptions();
		ChessBoard.promote(row, col, userPromoted);
	}
}

int Chess::GameState::displayPieceOptions()
{
	int promoted = -1;

	std::cout << "1: Queen (Default)" << std::endl;
	std::cout << "2: Rook" << std::endl;
	std::cout << "3: Bishop" << std::endl;
	std::cout << "4: Knight" << std::endl;
	std::cout << "Promote: ";

	std::cin >> promoted;
	
	// Default Queen will be put on the board if bad input
	if (promoted < 1 || promoted > 4)
		promoted = 1;

	return promoted;
}

void Chess::GameState::prompt(const char * message)
{
	std::cout << message;
}

void Chess::GameState::input(int & row, int & col, int & endRow, int & endCol)
{
	std::cin >> row;
	std::cin >> col;
	std::cin >> endRow;
	std::cin >> endCol;
}

Chess::GameState::~GameState()
{

}
