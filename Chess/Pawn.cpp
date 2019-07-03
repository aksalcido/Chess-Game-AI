#include "Pawn.h"

Chess::Pawn::Pawn(int newX, int newY, int newColor, char rep)
	: enpassant(false), GameObject(newX, newY, newColor, rep)
{

}

std::vector< std::pair<int, int> > Chess::Pawn::acquireMoves(Board * ChessBoard)
{
	moves.clear();

	forward(ChessBoard);
	diagonal(ChessBoard);

	return moves;
}

void Chess::Pawn::forward(Board * ChessBoard)
{
	int dx = (color == white ? -1 : 1);

	// If Pawn has not moved yet, then capable of moving up two spaces
	if (hasNotMoved && ChessBoard->emptySpace(x + 2 * dx, y))
	{
		moves.push_back(std::make_pair(x + 2 * dx, y));
	}

	// Pawn can also move up one space as long as the space is not occupied
	if (ChessBoard->emptySpace(x + 1 * dx, y))
	{
		moves.push_back(std::make_pair(x + 1 * dx, y));
	}
}

void Chess::Pawn::diagonal(Board * ChessBoard)
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