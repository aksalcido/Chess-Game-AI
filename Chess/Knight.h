#ifndef KNIGHT_H
#define KNIGHT_H

#pragma once
#include "GameObject.h"

namespace Chess {
	class Knight : public GameObject
	{
	public:
		Knight(int newX, int newY, int newColor, char rep);

		std::vector< std::pair<int, int> > acquireMoves(Board * ChessBoard) override;

		void jump(std::vector< std::pair<int, int> > & moves, Board * ChessBoard);

		~Knight();
	};
};

#endif // KNIGHT_H