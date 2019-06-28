#include "Board.h"
#include <iostream>

bool DEBUG = false;

Chess::Board::Board()
{
	initialize(board);
}

void Chess::Board::movementToEmptySquare(int row, int col, int endRow, int endCol)
{
	std::swap(board[row][col], board[endRow][endCol]);
}

void Chess::Board::movementToEnemy(int row, int col, int endRow, int endCol)
{
	delete board[endRow][endCol];
	board[endRow][endCol] = nullptr;

	std::swap(board[row][col], board[endRow][endCol]);
}

void Chess::Board::updateCoordinates(int newRow, int newCol)
{
	board[newRow][newCol]->changeCoordinates(newRow, newCol);
}

void Chess::Board::firstMoveCheck(int row, int col)
{
	board[row][col]->firstMoveOccured();
}

void Chess::Board::castlingCheck(int row, int col)
{
	if (pieceHasNotMoved(row, col) && (board[row][col] -> displayPiece() == 'K' || 'k') && (col == dimension - 2))
	{
		std::swap(board[row][col - 1], board[row][col + 1]);
	}
}

bool Chess::Board::pieceHasNotMoved(int row, int col)
{
	return board[row][col]->initialPosition();
}

bool Chess::Board::validMove(int row, int col, int endRow, int endCol)
{
	return board[row][col] -> validMove(endRow, endCol, this);
}

char Chess::Board::piece(int x, int y) const
{
	return board[x][y] -> displayPiece();
}

int Chess::Board::pieceColor(int x, int y) const
{
	return board[x][y] -> pieceColor();
}

bool Chess::Board::emptySpace(int dx, int dy) const
{
	return ( inBounds(dx, dy) ? board[dx][dy] == nullptr : false );
}

bool Chess::Board::enemySpace(int row, int col, int dx, int dy) const
{
	return (inBounds(dx, dy) ? (!emptySpace(dx, dy) && board[row][col]->oppositePlayer(pieceColor(dx, dy))) : false);
}

bool Chess::Board::inBounds(int row, int column) const
{
	return (0 <= row && row < dimension) && (0 <= column && column < dimension);
}

void Chess::Board::initialize(GameObject(*board[dimension][dimension]))
{
	// Initializes a Local representation of the Chess board to place Chess Objects onto the board
	char representation[dimension][dimension]
	{
		{ 'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R' },{ 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' },{ '.', '.', '.', '.', '.', '.', '.', '.' },{ '.', '.', '.', '.', '.', '.', '.', '.' },
		{ '.', '.', '.', '.', '.', '.', '.', '.' },{ '.', '.', '.', '.', '.', '.', '.', '.' },{ 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p' },{ 'r', 'h', 'b', 'q', 'k', 'b', 'h', 'r' },
	};

	for (unsigned int i = 0; i < dimension; i++)
	{
		for (unsigned int j = 0; j < dimension; j++)
		{
			char square = representation[i][j];

			switch (square) {

			case 'R':
				board[i][j] = new Rook(i, j, black, square);
				break;

			case 'r':
				board[i][j] = new Rook(i, j, white, square);
				break;

			case 'H':
				board[i][j] = new Knight(i, j, black, square);
				break;

			case 'h':
				board[i][j] = new Knight(i, j, white, square);
				break;

			case 'B':
				board[i][j] = new Bishop(i, j, black, square);
				break;

			case 'b':
				board[i][j] = new Bishop(i, j, white, square);
				break;

			case 'Q':
				board[i][j] = new Queen(i, j, black, square);
				break;

			case 'q':
				board[i][j] = new Queen(i, j, white, square);
				break;

			case 'K':
				board[i][j] = new King(i, j, black, square);
				break;

			case 'k':
				board[i][j] = new King(i, j, white, square);
				break;

			case 'P':
				board[i][j] = new Pawn(i, j, black, square);
				break;

			case 'p':
				board[i][j] = new Pawn(i, j, white, square);
				break;

			default:
				board[i][j] = nullptr;
				break;
			}
		}
	}
}


Chess::Board::~Board()
{
	for (unsigned int i = 0; i < dimension; i++) {
		for (unsigned int j = 0; j < dimension; j++) {
			if (board[i][j] != nullptr)
				delete board[i][j];
		}
	}
}