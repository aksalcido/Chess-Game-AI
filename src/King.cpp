#include "King.h"
#include <iostream>

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

Chess::King::King(const King & k) : checked(k.checked), castlingPosition(k.castlingPosition), paths(k.paths) {
	
}

Chess::King& Chess::King::operator=(const Chess::King& piece) {
	GameObject::operator=(piece);
	checked = piece.checked;
	castlingPosition = piece.castlingPosition;
	paths = piece.paths;

	return *this;
}

void Chess::King::copy(const GameObject* piece) {
	*this = *(King*)(piece);
}


bool Chess::King::inCheck() {
	return checked;
}

Moves Chess::King::acquireMoves(const Board* ChessBoard) {
	// Clears moves that might have been acquired in previous turns
	moves.clear();

	// Acquires moves that are possible given the current Chessboard accordingly to the King's movement pattern
	limitedMobility(ChessBoard);

	if (hasNotMoved) 
		castling(ChessBoard);

	// Will go through the 'moves' vector and dispose of the invalid moves due to the King being in Check
	if (playerInCheck(ChessBoard))
		moves = adjustMoves(ChessBoard);

	return moves;
}

std::vector <Moves> Chess::King::enemies() {
	return paths;
}

void Chess::King::limitedMobility(const Board* ChessBoard) {
	int dx, dy;

	for (int i = 0; i < directions.size(); i++) {
		dx = directions[i].dx;
		dy = directions[i].dy;

		if (ChessBoard->emptySpace(x + dx, y + dy) || ChessBoard->enemySpace(x, y, x + dx, y + dy))
			moves.push_back(std::make_pair(x + dx, y + dy));
	}
}

void Chess::King::castling(const Board* ChessBoard) {
	// Rook x-Coordinate for Castling which differs depending on which Player is trying to castle
	int rx = (color == white ? dimension - 1 : 0);

	// Rook y-Coordinate for Castling which will always be at the end of the board
	int ry = dimension - 1;
	
	if (ChessBoard->emptySpace(castlingPosition.first, castlingPosition.second - 1) && ChessBoard->emptySpace(castlingPosition.first, castlingPosition.second) &&
		ChessBoard->pieceHasNotMoved(rx, ry) ) {
		moves.push_back(std::make_pair(castlingPosition.first, castlingPosition.second));
	}
}

void Chess::King::checkedStatus(Board* ChessBoard) {
	// Local Boolean to check if a check occured during the last turn, that way 'checked' can be changed between true or false for each turn
	bool currentlyChecked = false;

	checkForEnemies(ChessBoard, currentlyChecked);
	checkForKnights(ChessBoard, currentlyChecked);

	// Updates the value of 'checked' for the King
	checked = currentlyChecked;
}

void Chess::King::checkForEnemies(const Board* ChessBoard, bool& currentlyChecked) {
	int dx, dy;
	Moves path;

	for (int d = 0; d < directions.size(); d++) {
		dx = directions[d].dx;
		dy = directions[d].dy;
		path.clear();


		while ((ChessBoard->inBounds(x + dx, y + dy))) {
			// Pushback the path that will get to the King -- there is also chances it won't in that case it will be discarded
			path.push_back(std::make_pair(x + dx, y + dy));

			// Continue the Search if the square is just an empty space
			if (ChessBoard->emptySpace(x + dx, y + dy)) {
				// increments dx and dy by whichever direction it is going
				incrementDirection(dx);
				incrementDirection(dy);
			}
				
			// Meaning there is a GameObject in the way -- Check if Enemy or Ally
			else {
				// If Enemy GameObject and can attack the King, then checked becomes True
				if (ChessBoard->enemySpace(x, y, x + dx, y + dy) && ChessBoard->enemyCheckingKing(x + dx, y + dy, x, y)) {
					currentlyChecked = true;
					paths.push_back(path);
				}

				break; // Break because a GameObject being in the King's Path will block other pieces from attacking the King
			}
		}
	}
}

void Chess::King::checkForKnights(const Board* ChessBoard, bool& currentlyChecked) {
	int dx, dy;

	std::vector<Direction> possibleKnights { 
		Direction{ -2, -1 }, Direction{ -1, -2 }, Direction{ 1, -2 }, Direction{ 2, -1 },
		Direction{ -2, 1 }, Direction{ -1, 2 }, Direction{ 1, 2 }, Direction{ 2, 1 } 
	};
	
	for (int d = 0; d < possibleKnights.size(); d++) {
		dx = possibleKnights[d].dx;
		dy = possibleKnights[d].dy;

		// If Enemy Knight is in the coordinates of the directions then the King is placed into check
		if (ChessBoard->enemySpace(x, y, x + dx, y + dy) && (ChessBoard->piece(x + dx, y + dy) == 'H' || ChessBoard->piece(x + dx, y + dy) == 'h')) {
			currentlyChecked = true;
			paths.push_back(Moves{ std::make_pair(x + dx, y + dy) });
		}
	}
}


Chess::King::~King() {

}