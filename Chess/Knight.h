#ifndef KNIGHT_H
#define KNIGHT_H

#pragma once
#include "GameObject.h"

namespace Chess {
	class Knight : public GameObject
	{
	public:
		// Knight Constructor that assigns the coordinate values with respective color and char representation for the GameObject
		Knight(int newX, int newY, int newColor, char rep);

		Knight & operator=(const Knight & piece);

		// Copies a Knight GameObject by proper pointer conversion on a GameObject and calling Knight's = operator
		void copy(const GameObject * piece) override;

		// Returns a vector of pairs of each possible move that can be made on the Board for the Knight
		Moves acquireMoves(Board * ChessBoard) override;

		~Knight();

	private:
		// Handles the Knight's jump movement that it can make on the Board. Adds each possible move as a pair of (row, column) to the 'moves' vector.
		void jump(Board * ChessBoard);
	};
};

#endif // KNIGHT_H