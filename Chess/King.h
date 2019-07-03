#ifndef KING_H
#define KING_H

#pragma once
#include "GameObject.h"

namespace Chess {
	class King : public GameObject
	{
	public:
		King(int newX, int newY, int newColor, char rep);

		bool recentlyCastled();

		bool inCheck();

		std::vector< std::pair<int, int> > acquireMoves(Board * ChessBoard) override;

		void limitedMobility(std::vector< std::pair<int, int> > & moves, Board * ChessBoard);

		void castling(std::vector< std::pair<int, int> > & moves, Board * ChessBoard);

		void checkForEnemies(Board * ChessBoard);

		~King();

	private:
		bool checked;
		std::pair<int, int> castlingPosition;

	};
};

#endif // KING_H