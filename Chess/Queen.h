#ifndef QUEEN_H
#define QUEEN_H

#pragma once
#include "GameObject.h"

namespace Chess {
	class Queen : public GameObject
	{
	public:
		// Queen Constructor that assigns the coordinate values with respective color and char representation for the GameObject
		Queen(int newX, int newY, int newColor, char rep);

		// Returns a vector of pairs of each possible move that can be made on the Board for the Queen
		std::vector< std::pair<int, int> > acquireMoves(Board * ChessBoard) override;

		~Queen();
	
	private:
		// Handles all movement that the Queen can make on the Board. Adds each possible move as a pair of (row, column) to the 'moves' vector.
		void mobility(Board * ChessBoard);
	};
};

#endif // QUEEN_H