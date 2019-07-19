#ifndef CHESS_AI_H
#define CHESS_AI_H

#include "GameObject.h"
#include <random>
#pragma once

#define EASY 0
#define NORMAL 1

#define MAX_DEPTH 3

typedef std::pair<std::pair<int, int>, std::pair<int, int>> Move;

namespace Chess {
	class ChessAI
	{
	public:
		// Default constructor for the AI
		ChessAI();

		Move chooseMove(Board * ChessBoard);

		void setDifficulty(int newDifficulty);

		~ChessAI();

	private:
		// Source of Entropy
		std::random_device device;

		int difficulty, color, maxDepth;

		Move easyMove(Board * ChessBoard);

		Move normalMove(Board * ChessBoard);

		// Easy AI will randomly choose a move with no proper strategy
		void random();

		// Normal AI will evaluate the board and choose a move that will be beneficial
		void search();

		int evaluate();

	};

}

#endif // CHESS_AI_H