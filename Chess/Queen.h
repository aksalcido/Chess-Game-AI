#ifndef QUEEN_H
#define QUEEN_H

#pragma once
#include "GameObject.h"

namespace Chess {
	class Queen : public GameObject
	{
	public:
		Queen(int newX, int newY, int newColor, char rep);

		void move() override;

		bool validMove(int row, int column, Board * ChessBoard) override;

		std::vector< std::pair<int, int> > acquireMoves(Board * ChessBoard) override;

		~Queen();
	};
};

#endif // QUEEN_H