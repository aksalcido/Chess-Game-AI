#ifndef KING_H
#define KING_H

#pragma once
#include "GameObject.h"

namespace Chess {
	class King : public GameObject
	{
	public:
		King(int newX, int newY, int newColor, char rep);

		void move() override;

		bool validMove(int row, int column, Board * ChessBoard) override;

		std::vector< std::pair<int, int> > acquireMoves(Board * ChessBoard) override;

		~King();

	private:
		bool inCheck;
	};
};

#endif // KING_H