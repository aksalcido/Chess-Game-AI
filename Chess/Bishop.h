#ifndef BISHOP_H
#define BISHOP_H

#pragma once
#include "GameObject.h"

namespace Chess {
	class Bishop : public GameObject
	{
	public:
		Bishop(int newX, int newY, int newColor, char rep);

		void move() override;

		bool validMove(int row, int column, Board * ChessBoard) override;

		std::vector< std::pair<int, int> > acquireMoves(Board * ChessBoard) override;

		~Bishop();
	};
};

#endif // BISHOP_H