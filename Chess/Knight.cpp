#include "Knight.h"

// ===== Knight Class ===== //
Chess::Knight::Knight(int newX, int newY, int newColor, char rep)
	: GameObject(newX, newY, newColor, rep)
{
	directions = std::vector<Direction>{
		Direction{ 1, 2 }, Direction{ 1, -2 }, Direction{ -1, 2 }, Direction{ -1, -2 },
		Direction{ 2, 1 }, Direction{ 2, -1 }, Direction{ -2, 1 }, Direction{ -2, -1 }
	};
}

std::vector< std::pair<int, int> > Chess::Knight::acquireMoves(Board * ChessBoard)
{
	moves.clear();
	jump(ChessBoard);

	return moves;
}

void Chess::Knight::jump(Board * ChessBoard)
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

Chess::Knight::~Knight()
{

}