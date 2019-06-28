#ifndef BISHOP_H
#define BISHOP_H

#pragma once
#include "GameObject.h"

namespace Chess {
	class Bishop : public GameObject
	{
	public:
		Bishop(int newX, int newY, int newColor, char rep);

		std::vector< std::pair<int, int> > acquireMoves(Board * ChessBoard) override;
		
		void diagonal(std::vector< std::pair<int, int> > & moves, Board * ChessBoard);

		~Bishop();

	};
};

#endif // BISHOP_H