#include "Board.h"
#include <iostream>

bool DEBUG = false;

Board::Board()
{
	initialize(board);
}

void Board::movementToEmptySquare(int row, int col, int endRow, int endCol)
{
	// DEBUG
	if (DEBUG) {
		std::pair<int, int> coords = board[row][col]->getCoordinates();
		std::cout << "x: " << coords.first << " y: " << coords.second << std::endl;
	}

	std::swap(board[row][col], board[endRow][endCol]);
}

void Board::movementToEnemy(int row, int col, int endRow, int endCol)
{
	delete board[endRow][endCol];
	board[endRow][endCol] = nullptr;

	std::swap(board[row][col], board[endRow][endCol]);
}

void Board::updateCoordinates(int newRow, int newCol)
{
	board[newRow][newCol]->changeCoordinates(newRow, newCol);

	// DEBUG
	if (DEBUG) {
		std::pair<int, int> coords = board[newRow][newCol]->getCoordinates();
		std::cout << "x: " << coords.first << " y: " << coords.second << std::endl;
	}
}

void Board::firstMoveCheck(int row, int col)
{
	board[row][col]->firstMoveOccured();
}

bool Board::validMove(int row, int col, int endRow, int endCol)
{
	// DEBUG
	if (DEBUG) {
		std::pair<int, int> coords = board[row][col]->getCoordinates();
		std::cout << "x: " << coords.first << " y: " << coords.second << std::endl;
	}

	return board[row][col] -> validMove(endRow, endCol, this);
}

char Board::piece(int x, int y) const
{
	return board[x][y] -> displayPiece();
}

int Board::pieceColor(int x, int y) const
{
	return board[x][y] -> pieceColor();
}

bool Board::emptySpace(int dx, int dy) const
{
	return ( inBounds(dx, dy) ? board[dx][dy] == nullptr : false );
}

bool Board::enemySpace(int row, int col, int dx, int dy) const
{
	return (inBounds(dx, dy) ? (!emptySpace(dx, dy) && board[row][col]->oppositePlayer(pieceColor(dx, dy))) : false);
}

bool Board::inBounds(int row, int column) const
{
	return (0 <= row && row < dimension) && (0 <= column && column < dimension);
}

void Board::initialize(Chess::GameObject(*board[dimension][dimension]))
{
	// Initializes a Local representation of the Chess board to place Chess Objects onto the board
	char representation[dimension][dimension]
	{
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
				board[i][j] = new Chess::Rook(i, j, black, square);
				break;

			case 'r':
				board[i][j] = new Chess::Rook(i, j, white, square);
				break;

			case 'H':
				board[i][j] = new Chess::Knight(i, j, black, square);
				break;

			case 'h':
				board[i][j] = new Chess::Knight(i, j, white, square);
				break;

			case 'B':
				board[i][j] = new Chess::Bishop(i, j, black, square);
				break;

			case 'b':
				board[i][j] = new Chess::Bishop(i, j, white, square);
				break;

			case 'Q':
				board[i][j] = new Chess::Queen(i, j, black, square);
				break;

			case 'q':
				board[i][j] = new Chess::Queen(i, j, white, square);
				break;

			case 'K':
				board[i][j] = new Chess::King(i, j, black, square);
				break;

			case 'k':
				board[i][j] = new Chess::King(i, j, white, square);
				break;

			case 'P':
				board[i][j] = new Chess::Pawn(i, j, black, square);
				break;

			case 'p':
				board[i][j] = new Chess::Pawn(i, j, white, square);
				break;

			default:
				board[i][j] = nullptr;
				break;
			}
		}
	}
}


Board::~Board()
{
	for (unsigned int i = 0; i < dimension; i++) {
		for (unsigned int j = 0; j < dimension; j++) {
			if (board[i][j] != nullptr)
				delete board[i][j];
		}
	}
}