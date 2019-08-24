#include "GameState.h"

Chess::GameState::GameState() : turn(white), GameOver(false)
{

}

void Chess::GameState::progress(int row, int col, int endRow, int endCol)
{
	movement(row, col, endRow, endCol);
	checksAndUpdates(endRow, endCol);
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

void Chess::GameState::progressAI()
{
	Move AI_Move = ChessBot.chooseMove(&ChessBoard);
	std::pair<int, int> start = AI_Move.first, end = AI_Move.second;

	// This while loop will only be called if the AI tries to do an illegal move which would put his King in Check
	while (! ChessBoard.safeMove(start.first, start.second, end.first, end.second))
	{
		AI_Move = ChessBot.chooseMove(&ChessBoard);
		start = AI_Move.first, end = AI_Move.second;
	}

	progress(start.first, start.second, end.first, end.second);
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

void Chess::GameState::initializeAI(int difficulty)
{
	ChessBot.setDifficulty(difficulty);
}

void Chess::GameState::checksAndUpdates(int row, int col)
{
	ChessBoard.castlingCheck(row, col);
	ChessBoard.firstMoveCheck(row, col);
	ChessBoard.updateCoordinates(row, col);
}

void Chess::GameState::nextTurn()
{
	turn = (turn == white ? black : white);
}

bool Chess::GameState::playersTurn()
{
	return turn == white;
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
	printf("   0 1 2 3 4 5 6 7\n -------------------\n");

	for (unsigned int i = 0; i < dimension; i++)
	{
		printf("%d| ", i);

		for (unsigned int j = 0; j < dimension; j++) {

			if (!ChessBoard.emptySpace(i, j))
				printf("%c ", ChessBoard.piece(i, j));

			else
				printf(". ");
		}

		printf("|\n");
	}
	printf(" -------------------\n");

	if (continuing())
		printf("It is %s's turn to move!\n", (turn == white ? "white" : "black"));
}

void Chess::GameState::displayMove(int startRow, int startColumn, int endRow, int endColumn) const
{
	printf("Move: (%d, %d) -> (%d, %d)\n", startRow, startColumn, endRow, endColumn);
}

void Chess::GameState::displayCheck() const
{
	const char * player = (turn == white ? "White" : "Black");
	printf("%s's king is in check!\n", player);
}

void Chess::GameState::displayWinner() const
{
	const char * winner;

	// Winner is the opposite player of the current turn
	if (ChessBoard.kingInCheck(turn))
	{
		winner = (turn == white ? "black" : "white");
		printf("CHECKMATE! The winner of the match is %s!\n", winner);
	}

	// STALEMATE !!!
	else {
		printf("The Game has ended in a Stalemate!\n");
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

	printf("1: Queen (Default)\n");
	printf("2: Rook\n");
	printf("3: Bishop\n");
	printf("4: Knight\n");
	printf("Promote: ");

	std::cin >> promoted;
	
	// Default -- Queen will be put on the board if receives Bad Input from User
	if (promoted < 1 || promoted > 4)
		promoted = 1;

	return promoted;
}

void Chess::GameState::prompt(const char * message)
{
	printf("%s", message);
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
