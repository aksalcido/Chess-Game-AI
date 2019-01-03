#include "Rook.h"

Chess::Rook::Rook(int newX, int newY, int newColor, char rep)
	: GameObject(newX, newY, newColor, rep)
{

}

void Chess::Rook::move()
{

}

bool Chess::Rook::validMove(int row, int column, Board * ChessBoard)
{
	std::vector< std::pair<int, int> > moves = acquireMoves(ChessBoard);

	for (std::vector< std::pair<int, int> >::iterator it = moves.begin(); it != moves.end(); ++it)
	{
		if (it->first == row && it->second == column)
			return true;
	}

	return false;
}

std::vector< std::pair<int, int> > Chess::Rook::acquireMoves(Board * ChessBoard)
{
	std::vector< std::pair<int, int> > moves;


	return moves;
}

Chess::Rook::~Rook()
{

}
