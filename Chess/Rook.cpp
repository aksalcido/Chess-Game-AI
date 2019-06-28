#include "Rook.h"

Chess::Rook::Rook(int newX, int newY, int newColor, char rep)
	: GameObject(newX, newY, newColor, rep)
{
	directions = std::vector<Direction>
	{
		Direction{ 1, 0 }, Direction{ 0, 1 }, Direction{ -1, 0 }, Direction{ 0, -1 }
	};
}

std::vector< std::pair<int, int> > Chess::Rook::acquireMoves(Board * ChessBoard)
{
	std::vector< std::pair<int, int> > moves;
	lateral(moves, ChessBoard);

	return moves;
}

void Chess::Rook::lateral(std::vector< std::pair<int, int > > & moves, Board * ChessBoard)
{
	int dx, dy;

	for (int d = 0; d < directions.size(); d++) {
		dx = directions[d].dx;
		dy = directions[d].dy;

		for (int i = 0; i < dimension; i++)
		{
			// loop continues if its empty because theres no end point reached
			if (ChessBoard->emptySpace(x + dx, y + dy)) {
				moves.push_back(std::make_pair(x + dx, y + dy));
			}

			// enemy would signify an endpoint, which requires the break
			else if (ChessBoard->enemySpace(x, y, x + dx, y + dy)) {
				moves.push_back(std::make_pair(x + dx, y + dy));
				break;
			}

			// if none of these occur, it means that there is no valid path left and must break
			else {
				break;
			}

			// increments dx and dy by whichever direction it is going
			dx = (dx == 0 ? 0 : (dx >= 1 ? dx + 1 : dx - 1));
			dy = (dy == 0 ? 0 : (dy >= 1 ? dy + 1 : dy - 1));
		}
	}
}

Chess::Rook::~Rook()
{

}
