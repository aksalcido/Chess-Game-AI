#ifndef ROOK_H
#define ROOK_H

#pragma once
#include "GameObject.h"

namespace Chess {
	class Rook : public GameObject
	{
	public:
		// Rook Constructor that assigns the coordinate values with respective color and char representation for the GameObject
		Rook(int newX, int newY, int newColor, char rep);

		// Returns a vector of pairs of each possible move that can be made on the Board for the Rook
		std::vector< std::pair<int, int> > acquireMoves(Board * ChessBoard) override;
		
		~Rook();

	private:
		// Handles lateral movement that the Rook can make on the Board. Adds each possible move as a pair of (row, column) to the 'moves' vector.
		void lateral(Board * ChessBoard);
	};
};

#endif // ROOK_H