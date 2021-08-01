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
		// These 2d arrays store the value of every position possible for each GameObject, every position is hardcoded 
		// accordingly to the source used above.
		int WhiteKingPositions[dimension][dimension], WhiteQueenPositions[dimension][dimension], WhiteRookPositions[dimension][dimension],
			WhiteBishopPositions[dimension][dimension], WhiteKnightPositions[dimension][dimension], WhitePawnPositions[dimension][dimension],
			BlackKingPositions[dimension][dimension], BlackQueenPositions[dimension][dimension], BlackRookPositions[dimension][dimension],
			BlackBishopPositions[dimension][dimension], BlackKnightPositions[dimension][dimension], BlackPawnPositions[dimension][dimension];

		// Sets up the WhiteGameObjectPosition and the BlackGameObjectPosition using the 2d array 'pos'
		void setup(int pos[dimension][dimension], int whitePos[dimension][dimension], int blackPos[dimension][dimension]);

		// Initialzies the WhiteKingPositions and the BlackKingPositions
		void initializeKingTable();

		// Initializes the WhiteQueenPositions and the BlackQueenPositions
		void initializeQueenTable();

		// Initializes the WhiteRookPositions and the BlackRookPositions
		void initializeRookTable();

		// Initializes the WhiteBishopPositions and the BlackBishopPositions
		void initializeBishopTable();

		// Initializes the WhiteKnightPositions and the BlackKnightPositions
		void initializeKnightTable();

		// Initializes the WhitePawnPositions and the BlackPawnPositions
		void initializePawnTable();
	};
}

#endif // TABLES_H
