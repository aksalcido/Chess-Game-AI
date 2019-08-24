#ifndef CHESS_AI_H
#define CHESS_AI_H

#include "Tables.h"
#include <random>
#include <algorithm>

#pragma once

#define EASY 0
#define NORMAL 1
#define MAX_DEPTH 2

typedef std::pair<std::pair<int, int>, std::pair<int, int>> Move;

namespace Chess {
	class ChessAI
	{
	public:
		// Default constructor for the AI
		ChessAI();

		// Assigns the Difficulty to the User Input argument 'newDifficulty' to the AI
		void setDifficulty(int newDifficulty);

		// Main function that chooses a move for the AI based on the difficulty
		Move chooseMove(Board * ChessBoard);

		~ChessAI();

	private:
		// Holds all the Positional values for the Chessboard
		Tables table;

		// Source of Entropy
		std::random_device device;

		int difficulty, color, maxDepth;

		// Function that handles movement for Easy Difficulty, based off random choices
		Move easyMove(Board * ChessBoard);

		// Function that handles movement for Normal Difficulty, based off the minmax algorithm with alpha-beta pruning
		Move normalMove(Board * ChessBoard);

		// Easy AI will randomly choose a move with no proper strategy using this function
		void random();

		// Normal AI will evaluate the board and choose a move that will be beneficial using minmax algorithm with alpha-beta pruning
		int search(int depth, const Board & ChessBoard, std::map<int, Move> & moveMap, int bonus, int turn, int alpha, int beta);

		// Simple evaluation basing purely off Piece Values and positions on the Chessboard
		int evaluate(const Board & ChessBoard, int bonus);

		// bonusPoints will go through specifics on the board and make judgements on awarding additional points based off positions
		int bonusPoints(int row, int column, char piece);
	};

}

#endif // CHESS_AI_H