#ifndef ROOK_H
#define ROOK_H

#pragma once
#include "GameObject.h"

namespace Chess {
	class Rook : public GameObject
	{
	public:
		Rook(int newX, int newY, int newColor, char rep);

		void move() override;

		bool validMove(int row, int column, Board * ChessBoard) override;

		std::vector< std::pair<int, int> > acquireMoves(Board * ChessBoard) override;

		~Rook();

	};
};

#endif // ROOK_H