#ifndef QUEEN_H
#define QUEEN_H

#pragma once
#include "GameObject.h"

namespace Chess {
	class Queen : public GameObject
	{
	public:
		Queen(int newX, int newY, int newColor, char rep);

		std::vector< std::pair<int, int> > acquireMoves(Board * ChessBoard) override;

		void mobility(std::vector< std::pair<int, int> > & moves, Board * ChessBoard);

		~Queen();

	};
};

#endif // QUEEN_H