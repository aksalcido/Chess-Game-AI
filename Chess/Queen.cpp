#include "Queen.h"

// ===== Queen Class ===== //
Chess::Queen::Queen(int newX, int newY, int newColor, char rep)
	: GameObject(newX, newY, newColor, rep)
{
	directions = std::vector<Direction>{
		Direction{ 1, 1 }, Direction{ 1, 0 }, Direction{ 0, 1 }, Direction{ -1, -1 },
		Direction{ -1, 0 }, Direction{ -1, 1 }, Direction{ 1, -1 }, Direction{ 0, -1 }
	};

}


void Chess::Queen::move()
{

}

bool Chess::Queen::validMove(int row, int column, Board * ChessBoard)
{
	return true;
}

std::vector< std::pair<int, int> > Chess::Queen::acquireMoves(Board * ChessBoard)
{
	std::vector< std::pair<int, int> > moves;




	return moves;
}

Chess::Queen::~Queen()
{

}