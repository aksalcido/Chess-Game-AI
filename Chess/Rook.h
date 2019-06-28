#ifndef ROOK_H
#define ROOK_H

#pragma once
#include "GameObject.h"

namespace Chess {
	class Rook : public GameObject
	{
	public:
		Rook(int newX, int newY, int newColor, char rep);

		std::vector< std::pair<int, int> > acquireMoves(Board * ChessBoard) override;
		
		void lateral(std::vector< std::pair<int, int > > & moves, Board * ChessBoard);
		
		~Rook();

	};
};

#endif // ROOK_H