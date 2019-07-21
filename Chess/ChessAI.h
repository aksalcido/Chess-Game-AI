#ifndef CHESS_AI_H
#define CHESS_AI_H

#include "Tables.h"
#include <random>
#include <algorithm>
#pragma once

#define EASY 0
#define NORMAL 1

#define MAX_DEPTH 5

typedef std::pair<std::pair<int, int>, std::pair<int, int>> Move;

namespace Chess {
	class ChessAI
	{
	public:
		// Default constructor for the AI
		ChessAI();

		void setDifficulty(int newDifficulty);

		Move chooseMove(Board * ChessBoard);

		~ChessAI();

	private:
		Tables table;

		// Source of Entropy
		std::random_device device;

		int difficulty, color, maxDepth;

		Move easyMove(Board * ChessBoard);

		Move normalMove(Board * ChessBoard);

		// Easy AI will randomly choose a move with no proper strategy
		void random();

		// Normal AI will evaluate the board and choose a move that will be beneficial using minmax algorithm
		int search(int depth, const Board & ChessBoard, std::map<int, Move> & moveMap, int bonus);

		// Simple evaluation basing purely off Piece Values
		int evaluate(const Board & ChessBoard, int bonus);

		// bonusPoints will go through specifics on the board and make judgements on awarding additional points based off positions
		int bonusPoints(int row, int column, char piece);
	};

}

#endif // CHESS_AI_H