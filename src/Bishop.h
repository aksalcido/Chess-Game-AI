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

		Bishop & operator=(const Bishop & piece);

		// Copies a Bishop GameObject by proper pointer conversion on a GameObject and calling Bishop's = operator
		void copy(const GameObject * piece) override;

		// Returns a vector of pairs of each possible move that can be made on the Board for the Bishop
		Moves acquireMoves(const Board * ChessBoard) override;

		~Bishop();

	private:
		// Handles diagonal movement that the Bishop can make on the Board. Adds each possible move as a pair of (row, column) to the 'moves' vector.
		void diagonal(const Board * ChessBoard);
	};
};

#endif // BISHOP_H