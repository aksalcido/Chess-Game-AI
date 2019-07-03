#ifndef PAWN_H
#define PAWN_H

#pragma once
#include "GameObject.h"

namespace Chess {
	class Pawn : public GameObject
	{
	public:
		// Pawn Constructor that assigns the coordinate values with respective color and char representation for the GameObject
		Pawn(int newX, int newY, int newColor, char rep);

		// Returns a vector of pairs of each possible move that can be made on the Board for the Pawn
		std::vector< std::pair<int, int> > acquireMoves(Board * ChessBoard) override;

		~Pawn();

	private:
		bool enpassant;

		// Handles diagonal movement that the Pawn can make on the Board when there is an enemy in there. Adds each possible move as a pair of (row, column) to the 'moves' vector.
		void diagonal(Board * ChessBoard);

		// Handles forward movement that the Pawn can make on the Board. Adds each possible move as a pair of (row, column) to the 'moves' vector.
		void forward(Board * ChessBoard);
	};

}

#endif // PAWN_H