#ifndef BISHOP_H
#define BISHOP_H

#pragma once
#include "GameObject.h"

namespace Chess {
	class Bishop : public GameObject
	{
	public:
		// Bishop Constructor that assigns the coordinate values with respective color and char representation for the GameObject
		Bishop(int newX, int newY, int newColor, char rep);

		// Returns a vector of pairs of each possible move that can be made on the Board for the Bishop
		std::vector< std::pair<int, int> > acquireMoves(Board * ChessBoard) override;

		~Bishop();

	private:
		// Handles diagonal movement that the Bishop can make on the Board. Adds each possible move as a pair of (row, column) to the 'moves' vector.
		void diagonal(Board * ChessBoard);
	};
};

#endif // BISHOP_H