#include "King.h"

Chess::King::King(int newX, int newY, int newColor, char rep)
	: inCheck(false), GameObject(newX, newY, newColor, rep)
{
	directions = std::vector<Direction>
	{
		Direction{ 1, 1 }, Direction{ 1, 0 }, Direction{ 0, 1 }, Direction{ -1, -1 },
		Direction{ -1, 0 }, Direction{ -1, 1 }, Direction{ 1, -1 }, Direction{ 0, -1 }
	};

	castlingPosition = std::pair<int, int>{ x, y + 2 };
}

std::vector< std::pair<int, int> > Chess::King::acquireMoves(Board * ChessBoard)
{
	std::vector< std::pair<int, int> > moves;
	limitedMobility(moves, ChessBoard);
	
	if (hasNotMoved)
		castling(moves, ChessBoard);

	return moves;
}

void Chess::King::limitedMobility(std::vector< std::pair<int, int> > & moves, Board * ChessBoard)
{
	int dx, dy;

	for (int i = 0; i < directions.size(); i++)
	{
		dx = directions[i].dx;
		dy = directions[i].dy;

		if (ChessBoard->emptySpace(x + dx, y + dy) || ChessBoard->enemySpace(x, y, x + dx, y + dy))
		{
			moves.push_back(std::make_pair(x + dx, y + dy));
		}
	}
}

void Chess::King::castling(std::vector< std::pair<int, int> > & moves, Board * ChessBoard)
{
	// Rook Coordinate
	int rx = (color == white ? dimension - 1 : 0);
	int ry = dimension - 1;
	
	if (ChessBoard->emptySpace(castlingPosition.first, castlingPosition.second - 1) && ChessBoard->emptySpace(castlingPosition.first, castlingPosition.second) &&
		ChessBoard->pieceHasNotMoved(rx, ry) )
	{
		moves.push_back(std::make_pair(castlingPosition.first, castlingPosition.second));
	}
}



Chess::King::~King()
{

}