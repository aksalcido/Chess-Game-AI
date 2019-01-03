#include "King.h"

Chess::King::King(int newX, int newY, int newColor, char rep)
	: inCheck(false), GameObject(newX, newY, newColor, rep)
{
	directions = std::vector<Direction>
	{
		Direction{ 1, 1 }, Direction{ 1, 0 }, Direction{ 0, 1 }, Direction{ -1, -1 },
		Direction{ -1, 0 }, Direction{ -1, 1 }, Direction{ 1, -1 }, Direction{ 0, -1 }
	};

}

void Chess::King::move()
{

}

bool Chess::King::validMove(int row, int column, Board * ChessBoard)
{
	return true;
}

std::vector< std::pair<int, int> > Chess::King::acquireMoves(Board * ChessBoard)
{
	std::vector< std::pair<int, int> > moves;




	return moves;
}


Chess::King::~King()
{

}