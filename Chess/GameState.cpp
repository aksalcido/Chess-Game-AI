#include "GameState.h"

GameState::GameState() : turn(white), GameOver(false)
{
	initialize(board);
}

bool GameState::validateMove(int row, int col, int endRow, int endCol)
{
	// Within Boundaries of the Board for Start/End Coordinates
	if (inBounds(row, col) && inBounds(endRow, endCol)) {

		// Start Position must be a GameObject
		if (board[row][col] != nullptr && board[row][col]->pieceColor() == turn) {
			return board[row][col]->validMove(endRow, endCol, board);
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
			if (board[i][j] != nullptr)
				std::cout << board[i][j]->displayPiece() << " ";
			else
				std::cout << ". ";
		}

		std::cout << "|" << std::endl;
	}

	std::cout << " -------------------" << std::endl;

	if (!GameOver)
		std::cout << "It is " << (turn == white ? "white's " : "black's ") << "turn to move!" << std::endl;
}


bool GameState::inBounds(int row, int column)
{
	return (0 <= row && row < dimension) && (0 <= column && column < dimension);
}


void GameState::initialize(Chess::GameObject(*board[dimension][dimension]))
{
	// Initializes a Local representation of the Chess board to place Chess Objects onto the board
	char representation[dimension][dimension]{
		{ 'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R' },{ 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' },{ '.', '.', '.', '.', '.', '.', '.', '.' },{ '.', '.', '.', '.', '.', '.', '.', '.' },
	{ '.', '.', '.', '.', '.', '.', '.', '.' },{ '.', '.', '.', '.', '.', '.', '.', '.' },{ 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p' },{ 'r', 'h', 'b', 'k', 'q', 'b', 'h', 'r' },
	};

	for (unsigned int i = 0; i < dimension; i++)
	{
		for (unsigned int j = 0; j < dimension; j++)
		{
			char square = representation[i][j];

			switch (square) {

			case 'R':
				board[i][j] = new Chess::Rook(j, i, black, square);
				break;

			case 'r':
				board[i][j] = new Chess::Rook(j, i, white, square);
				break;

			case 'H':
				board[i][j] = new Chess::Knight(j, i, black, square);
				break;

			case 'h':
				board[i][j] = new Chess::Knight(j, i, white, square);
				break;

			case 'B':
				board[i][j] = new Chess::Bishop(j, i, black, square);
				break;

			case 'b':
				board[i][j] = new Chess::Bishop(j, i, white, square);
				break;

			case 'Q':
				board[i][j] = new Chess::Queen(j, i, black, square);
				break;

			case 'q':
				board[i][j] = new Chess::Queen(j, i, white, square);
				break;

			case 'K':
				board[i][j] = new Chess::King(j, i, black, square);
				break;

			case 'k':
				board[i][j] = new Chess::King(j, i, white, square);
				break;

			case 'P':
				board[i][j] = new Chess::Pawn(j, i, black, square);
				break;

			case 'p':
				board[i][j] = new Chess::Pawn(j, i, white, square);
				break;

			default:
				board[i][j] = nullptr;
				break;
			}
		}
	}
}

GameState::~GameState()
{
	for (unsigned int i = 0; i < dimension; i++) {
		for (unsigned int j = 0; j < dimension; j++) {
			if (board[i][j] != nullptr)
				delete board[i][j];
		}
	}
}
