#ifndef PAWN_H
#define PAWN_H

#pragma once
#include "GameObject.h"

namespace Chess {
	class Pawn : public GameObject
	{
	public:
		Pawn(int newX, int newY, int newColor, char rep);

		void move() override;

		// Overrided validMove from base class GameObject, and returns a boolean if the row, column arguments are a valid move on the current Board.
		bool validMove(int row, int column, Board * ChessBoard) override;

		std::vector< std::pair<int, int> > acquireMoves(Board * ChessBoard) override;

		void diagonal(std::vector< std::pair<int, int> > & moves, Board * ChessBoard);

		void forward(std::vector< std::pair<int, int> > & moves, Board * ChessBoard);

		~Pawn();

	private:
		bool enpassant;

	};

}

#endif // PAWN_H