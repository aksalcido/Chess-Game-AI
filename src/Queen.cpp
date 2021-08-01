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

Chess::Queen& Chess::Queen::operator=(const Chess::Queen& piece) {
	GameObject::operator=(piece);

	return *this;
}

void Chess::Queen::copy(const GameObject* piece) {
	*this = *(Queen*)(piece);
}

Moves Chess::Queen::acquireMoves(const Board* ChessBoard) {
	// Clears moves that might have been acquired in previous turns
	moves.clear();

	// Acquires moves that are possible given the current Chessboard accordingly to the Queen's movement pattern
	mobility(ChessBoard);

	// Will go through the 'moves' vector and dispose of the invalid moves due to the King being in Check
	if (playerInCheck(ChessBoard))
		moves = adjustMoves(ChessBoard);

	return moves;
}

void Chess::Queen::mobility(const Board* ChessBoard) {
	int dx, dy;

	for (int d = 0; d < directions.size(); d++) {
		dx = directions[d].dx;
		dy = directions[d].dy;

		for (int i = 0; i < dimension; i++) {
			// loop continues if its empty because theres no end point reached
			if (ChessBoard->emptySpace(x + dx, y + dy))
				moves.push_back(std::make_pair(x + dx, y + dy));

			// enemy would signify an endpoint, which requires the break
			else if (ChessBoard->enemySpace(x, y, x + dx, y + dy)) {
				moves.push_back(std::make_pair(x + dx, y + dy));
				break;
			}

			// if none of these occur, it means that there is no valid path left and must break
			else
				break;

			// increments dx and dy by whichever direction it is going
			incrementDirection(dx);
			incrementDirection(dy);
		}
	}
}


Chess::Queen::~Queen() {

}