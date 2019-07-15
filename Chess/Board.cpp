#include "Board.h"
#include <iostream>

bool DEBUG = false;

Chess::Board::Board()
{
	initialize(board);
}

Chess::Board::Board(const Board & b)
{
	copy(b);
}

void Chess::Board::movementToEmptySquare(int row, int col, int endRow, int endCol)
{
	std::swap(board[row][col], board[endRow][endCol]);
}

void Chess::Board::movementToEnemy(int row, int col, int endRow, int endCol)
{
	updatePieces(board[endRow][endCol]);
	delete board[endRow][endCol];
	board[endRow][endCol] = nullptr;

	std::swap(board[row][col], board[endRow][endCol]);
}

void Chess::Board::updateCoordinates(int newRow, int newCol)
{
	board[newRow][newCol]->changeCoordinates(newRow, newCol);
}

void Chess::Board::playerStatus()
{
	((King*)blackKing)->checkedStatus(this);

	((King*)whiteKing)->checkedStatus(this);

	if (DEBUG) {
		std::cout << " whiteKing in Check: " << (((King*)whiteKing)->inCheck() ? "True" : "False") << std::endl;
		std::cout << " blackKing in Check: " << (((King*)blackKing)->inCheck() ? "True" : "False") << std::endl;

		std::cout << " board[7][5] == nullptr: " << (board[7][5] == nullptr) << std::endl;
		std::cout << " board[7][7] == nullptr: " << (board[7][7] == nullptr) << std::endl;
	}
}

void Chess::Board::firstMoveCheck(int row, int col)
{
	board[row][col]->firstMoveOccured();
}

void Chess::Board::castlingCheck(int row, int col)
{
	if (pieceHasNotMoved(row, col) && (piece(row, col) == BLACK_KING || piece(row,col) == WHITE_KING) && (col == dimension - 2))
	{
		std::swap(board[row][col - 1], board[row][col + 1]);
		board[row][col - 1] -> changeCoordinates(row, col - 1); // change coordinates of Rook after castling
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


bool Chess::Board::safeMove(int row, int col, int endRow, int endCol)
{
	std::unique_ptr<Board> copy = clone();

	if (copy->emptySpace(endRow, endCol))
	{
		copy->movementToEmptySquare(row, col, endRow, endCol);
	}
	else
	{
		copy->movementToEnemy(row, col, endRow, endCol);
	}

	copy->updateCoordinates(endRow, endCol);
	copy->playerStatus();

	return ! copy->kingInCheck(pieceColor(row, col));
}


bool Chess::Board::emptySpace(int row, int col) const
{
	return ( inBounds(row, col) ? board[row][col] == nullptr : false );
}

bool Chess::Board::enemySpace(int row, int col, int dx, int dy) const
{
	if (inBounds(dx, dy))
	{
		return !emptySpace(dx, dy) && board[row][col]->oppositePlayer(pieceColor(dx, dy));
	}

	return false;
}

bool Chess::Board::enemyCheckingKing(int enemyRow, int enemyCol, int kingRow, int kingCol)
{
	return board[enemyRow][enemyCol]->canAttackEnemy(kingRow, kingCol, this);
}

bool Chess::Board::inBounds(int row, int col) const
{
	return (0 <= row && row < dimension) && (0 <= col && col < dimension);
}


bool Chess::Board::kingInCheck(int color) const
{
	if (color == white)
		return ((King*)whiteKing)->inCheck();
	else
		return ((King*)blackKing)->inCheck();
}


char Chess::Board::piece(int row, int col) const
{
	return board[row][col]->displayPiece();
}

int Chess::Board::pieceColor(int row, int col) const
{
	return board[row][col]->pieceColor();
}

void Chess::Board::updatePieces(GameObject * pieceBeingRemoved)
{
	std::vector<GameObject*> * container = &(pieceBeingRemoved->pieceColor() == white ? whitePieces : blackPieces);

	for (int i = 0; i < container->size(); i++)
	{
		if ((*container)[i] == pieceBeingRemoved)
		{
			container->erase((*container).begin() + i);
		}
	}

	if (DEBUG) {
		std::cout << "WhitePieces.size(): " << whitePieces.size() << std::endl;
		std::cout << "BlackPieces.size(): " << blackPieces.size() << std::endl;
	}
}

std::vector<Moves> Chess::Board::enemyPaths(int color)
{
	if (color == white)
		return ((King*)whiteKing)->enemies();
	else
		return ((King*)blackKing)->enemies();
}


std::unique_ptr<Chess::Board> Chess::Board::clone()
{
	Board * newBoard = new Board(*this);
	std::unique_ptr<Board> board_ptr = std::make_unique<Board>( *newBoard );

	return board_ptr;
}

void Chess::Board::copy(const Board & otherBoard)
{
	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			char statement = otherBoard.board[i][j] != nullptr ? otherBoard.board[i][j]->displayPiece() : 'D';

			switch (statement)
			{

			case BLACK_ROOK:
				board[i][j] = new Rook(i, j, black, BLACK_ROOK);
				break;

			case WHITE_ROOK:
				board[i][j] = new Rook(i, j, white, WHITE_ROOK);
				break;

			case BLACK_KNIGHT:
				board[i][j] = new Knight(i, j, black, BLACK_KNIGHT);
				break;

			case WHITE_KNIGHT:
				board[i][j] = new Knight(i, j, white, WHITE_KNIGHT);
				break;

			case BLACK_BISHOP:
				board[i][j] = new Bishop(i, j, black, BLACK_BISHOP);
				break;

			case WHITE_BISHOP:
				board[i][j] = new Bishop(i, j, white, WHITE_BISHOP);
				break;

			case BLACK_QUEEN:
				board[i][j] = new Queen(i, j, black, BLACK_QUEEN);
				break;

			case WHITE_QUEEN:
				board[i][j] = new Queen(i, j, white, WHITE_QUEEN);
				break;

			case BLACK_KING:
				board[i][j] = new King(i, j, black, BLACK_KING);
				blackKing = board[i][j];
				break;

			case WHITE_KING:
				board[i][j] = new King(i, j, white, WHITE_KING);
				whiteKing = board[i][j];
				break;

			case BLACK_PAWN:
				board[i][j] = new Pawn(i, j, black, BLACK_PAWN);
				break;

			case WHITE_PAWN:
				board[i][j] = new Pawn(i, j, white, WHITE_PAWN);
				break;

			default:
				board[i][j] = nullptr;
				break;
			}

			if (board[i][j] != nullptr)
				board[i][j]->copy(otherBoard.board[i][j]);
		}
	}
}



void Chess::Board::initialize(GameObject(*board[dimension][dimension]))
{
	// Initializes a Local representation of the Chess board to place Chess Objects onto the board
	char representation[dimension][dimension]
	{
		{ 'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R' },
		{ 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' },
		{ '.', '.', '.', '.', '.', '.', '.', '.' },
		{ '.', '.', '.', '.', '.', '.', '.', '.' },
		{ '.', '.', '.', '.', '.', '.', '.', '.' },
		{ '.', '.', '.', '.', '.', '.', '.', '.' },
		{ 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p' },
		{ 'r', 'h', 'b', 'q', 'k', 'b', 'h', 'r' },
	};

	for (unsigned int i = 0; i < dimension; i++)
	{
		for (unsigned int j = 0; j < dimension; j++)
		{
			switch (representation[i][j]) {

			case BLACK_ROOK:
				board[i][j] = new Rook(i, j, black, BLACK_ROOK);
				break;

			case WHITE_ROOK:
				board[i][j] = new Rook(i, j, white, WHITE_ROOK);
				break;

			case BLACK_KNIGHT:
				board[i][j] = new Knight(i, j, black, BLACK_KNIGHT);
				break;

			case WHITE_KNIGHT:
				board[i][j] = new Knight(i, j, white, WHITE_KNIGHT);
				break;

			case BLACK_BISHOP:
				board[i][j] = new Bishop(i, j, black, BLACK_BISHOP);
				break;

			case WHITE_BISHOP:
				board[i][j] = new Bishop(i, j, white, WHITE_BISHOP);
				break;

			case BLACK_QUEEN:
				board[i][j] = new Queen(i, j, black, BLACK_QUEEN);
				break;

			case WHITE_QUEEN:
				board[i][j] = new Queen(i, j, white, WHITE_QUEEN);
				break;

			case BLACK_KING:
				board[i][j] = new King(i, j, black, BLACK_KING);
				blackKing = board[i][j];
				break;

			case WHITE_KING:
				board[i][j] = new King(i, j, white, WHITE_KING);
				whiteKing = board[i][j];
				break;

			case BLACK_PAWN:
				board[i][j] = new Pawn(i, j, black, BLACK_PAWN);
				break;

			case WHITE_PAWN:
				board[i][j] = new Pawn(i, j, white, WHITE_PAWN);
				break;

			default:
				board[i][j] = nullptr;
				break;
			}

			if (board[i][j] != nullptr && board[i][j]->pieceColor() == black)
			{
				blackPieces.push_back(board[i][j]);
			}

			else if (board[i][j] != nullptr && board[i][j]->pieceColor() == white)
			{
				whitePieces.push_back(board[i][j]);
			}

		}
	}
}


Chess::Board::~Board()
{
	std::cout << "Board Destructor Called" << std::endl;

	for (unsigned int i = 0; i < dimension; i++) {
		for (unsigned int j = 0; j < dimension; j++) {
			if (board[i][j] != nullptr)
				delete board[i][j];
		}
	}
}