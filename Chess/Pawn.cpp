#include "Pawn.h"

Chess::Pawn::Pawn(int newX, int newY, int newColor, char rep)
	: enpassant(false), GameObject(newX, newY, newColor, rep)
{

}


Chess::Pawn& Chess::Pawn::operator=(const Chess::Pawn & piece)
{
	GameObject::operator=(piece);
	enpassant = piece.enpassant;

	return *this;
}

void Chess::Pawn::copy(const GameObject * piece)
{
	*this = *(Pawn*)(piece);
}

Moves Chess::Pawn::acquireMoves(const Board * ChessBoard)
{
	// Clears moves that might have been acquired in previous turns
	moves.clear();

	// Acquires moves that are possible given the current Chessboard accordingly to the Pawn's movement pattern
	forward(ChessBoard);
	diagonal(ChessBoard);

	// Will go through the 'moves' vector and dispose of the invalid moves due to the King being in Check
	if (playerInCheck(ChessBoard))
	{
		moves = adjustMoves(ChessBoard);
	}

	return moves;
}

void Chess::Pawn::forward(const Board * ChessBoard)
{
	int dx = (color == white ? -1 : 1);

	// If Pawn has not moved yet, then capable of moving up two spaces
	if (hasNotMoved && ChessBoard->emptySpace(x + 2 * dx, y) && ChessBoard->emptySpace(x + 1 * dx, y))
	{
		moves.push_back(std::make_pair(x + 2 * dx, y));
	}

	// Pawn can also move up one space as long as the space is not occupied
	if (ChessBoard->emptySpace(x + 1 * dx, y))
	{
		moves.push_back(std::make_pair(x + 1 * dx, y));
	}
}

void Chess::Pawn::diagonal(const Board * ChessBoard)
{
	int dx = x + (color == white ? -1 : 1);

	// If the space is not empty and is occupied by an enemy, then it is possible for the Pawn to move there
	//if (!ChessBoard -> emptySpace(dx, y - 1) && oppositePlayer(ChessBoard -> pieceColor(dx, y-1)))
	if (ChessBoard->enemySpace(x, y, dx, y - 1))
	{
		moves.push_back(std::make_pair(dx, y - 1));
	}

	//if (!ChessBoard -> emptySpace(dx, y + 1) && oppositePlayer(ChessBoard -> pieceColor(dx, y + 1)))
	if (ChessBoard->enemySpace(x, y, dx, y + 1))
	{
		moves.push_back(std::make_pair(dx, y + 1));
	}
}

Chess::Pawn::~Pawn()
{

}