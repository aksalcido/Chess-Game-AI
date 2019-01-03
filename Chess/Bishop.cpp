#include "Bishop.h"

Chess::Bishop::Bishop(int newX, int newY, int newColor, char rep)
	: GameObject(newX, newY, newColor, rep)
{

}


void Chess::Bishop::move()
{

}

bool Chess::Bishop::validMove(int row, int column, Board * ChessBoard)
{
	return true;
}

std::vector< std::pair<int, int> > Chess::Bishop::acquireMoves(Board * ChessBoard)
{
	std::vector< std::pair<int, int> > moves;




	return moves;
}

Chess::Bishop::~Bishop()
{

}