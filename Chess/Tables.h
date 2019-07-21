#ifndef TABLES_H
#define TABLES_H
#include "GameObject.h"

#pragma once

namespace Chess {
	class Tables
	{
	public:
		// Initializes a Tables() class that will improve the decisions made by the ChessAI by having arrays containing values for each Game Piece move that can be made
		// Credit to the Value arrays goes to: https://www.freecodecamp.org/news/simple-chess-ai-step-by-step-1d55a9266977/
		// The arrays are hard-coded and unfortunately resulting in a lot of space to hold them -- meaning initializing is the worse performance.
		// On the positive, the central function get will be O(1) time complexity by direct access of the arrays.
		Tables();

		// 'get' will take a row and column argument given by the ChessAI, determine which array to look at by the 'piece', and will return the value of the position.
		int get(int row, int column, char piece);

		~Tables();

	private:
		int WhiteKingPositions[dimension][dimension], WhiteQueenPositions[dimension][dimension], WhiteRookPositions[dimension][dimension],
			WhiteBishopPositions[dimension][dimension], WhiteKnightPositions[dimension][dimension], WhitePawnPositions[dimension][dimension],
			BlackKingPositions[dimension][dimension], BlackQueenPositions[dimension][dimension], BlackRookPositions[dimension][dimension],
			BlackBishopPositions[dimension][dimension], BlackKnightPositions[dimension][dimension], BlackPawnPositions[dimension][dimension];
		
		void setup(int pos[dimension][dimension], int whitePos[dimension][dimension], int blackPos[dimension][dimension]);

		void initializeKingTable();

		void initializeQueenTable();

		void initializeRookTable();

		void initializeBishopTable();

		void initializeKnightTable();

		void initializePawnTable();
	};
}

#endif // TABLES_H
