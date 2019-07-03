#include "King.h"

Chess::King::King(int newX, int newY, int newColor, char rep)
	: checked(false), GameObject(newX, newY, newColor, rep)
{
	directions = std::vector<Direction>
	{
		Direction{ 1, 1 }, Direction{ 1, 0 }, Direction{ 0, 1 }, Direction{ -1, -1 },
		Direction{ -1, 0 }, Direction{ -1, 1 }, Direction{ 1, -1 }, Direction{ 0, -1 }
	};

	castlingPosition = std::pair<int, int>{ x, y + 2 };
}

bool Chess::King::inCheck()
{
	return checked;
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

void Chess::King::checkForEnemies(Board * ChessBoard)
{
	int dx, dy;

	for (int d = 0; d < directions.size(); d++)
	{
		dx = directions[d].dx;
		dy = directions[d].dy;

		for (int i = 0; i < dimension; i++) {
			
			if (ChessBoard->inBounds(x + dx, y + dy))
			{
				// Continue the Search if the square is just an empty space
				if (ChessBoard->emptySpace(x + dx, y + dy)) {
					// increments dx and dy by whichever direction it is going
					dx = (dx > 0 ? dx + 1 : dx - 1);
					dy = (dy > 0 ? dy + 1 : dy - 1);
				}
				
				// Meaning there is a GameObject in the way -- Check if Enemy or Ally
				else {

					// If Enemy GameObject and can attack the King, then checked becomes True
					if (ChessBoard->enemySpace(x, y, x + dx, y + dy) && ChessBoard->enemyCheckingKing(x + dx, y + dy, x, y))
					{
						checked = true;
					}

					break; // Break because a GameObject being in the King's Path will block other pieces from attacking the King
				}

			}

			else {
				break;
			}
		}
	}
}


Chess::King::~King()
{

}