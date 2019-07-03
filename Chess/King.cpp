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
	moves.clear();

	limitedMobility(ChessBoard);
	
	if (hasNotMoved)
		castling(ChessBoard);

	return moves;
}

void Chess::King::limitedMobility(Board * ChessBoard)
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

void Chess::King::castling(Board * ChessBoard)
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

void Chess::King::checkedStatus(Board * ChessBoard)
{
	// Local Boolean to check if a check occured during the last turn, that way 'checked' can be changed between true or false for each turn
	bool currentlyChecked = false;
	checkForEnemies(ChessBoard, currentlyChecked);
	checkForKnights(ChessBoard, currentlyChecked);
	checked = currentlyChecked;
}

void Chess::King::checkForEnemies(Board * ChessBoard, bool & currentlyChecked)
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
						currentlyChecked = true;
					}

					break; // Break because a GameObject being in the King's Path will block other pieces from attacking the King
				}

			}
			
			break; // Break because if the coordinates (dx, dy) are out of bounds then being checked from that Direction is impossible
		}
	}
}

void Chess::King::checkForKnights(Board * ChessBoard, bool & currentlyChecked)
{
	int dx, dy;

	std::vector<Direction> possibleKnights
	{ 
		Direction{ -2, -1 }, Direction{ -1, -2 }, Direction{ 1, -2 }, Direction{ 2, -1 },
		Direction{ -2, 1 }, Direction{ -1, 2 }, Direction{ 1, 2 }, Direction{ 2, 1 } 
	};
	
	for (int d = 0; d < possibleKnights.size(); d++)
	{
		dx = possibleKnights[d].dx;
		dy = possibleKnights[d].dy;

		// If Enemy Knight is in the coordinates of the directions then the King is placed into check
		if (ChessBoard->enemySpace(x, y, x + dx, y + dy) && ChessBoard->piece(x + dx, y + dy) == 'H' | 'h')
			currentlyChecked = true;
	}

}


Chess::King::~King()
{

}