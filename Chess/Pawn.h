#ifndef PAWN_H
#define PAWN_H

#pragma once
#include "GameObject.h"

namespace Chess {
	class Pawn : public GameObject
	{
	public:
		Pawn(int newX, int newY, int newColor, char rep);

		std::vector< std::pair<int, int> > acquireMoves(Board * ChessBoard) override;

		void diagonal(std::vector< std::pair<int, int> > & moves, Board * ChessBoard);

		void forward(std::vector< std::pair<int, int> > & moves, Board * ChessBoard);

		~Pawn();

	private:
		bool enpassant;

	};

}

#endif // PAWN_H