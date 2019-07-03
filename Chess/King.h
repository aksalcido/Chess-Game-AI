#ifndef KING_H
#define KING_H

#pragma once
#include "GameObject.h"

namespace Chess {
	class King : public GameObject
	{
	public:
		// King Constructor that assigns the coordinate values with respective color and char representation for the GameObject
		King(int newX, int newY, int newColor, char rep);

		// Goes through possible threats and checks if the King is currently in check, if so 'checked' boolean is changed to True. False otherwise
		void checkedStatus(Board * ChessBoard);

		// Returns a boolean True if checked. False otherwise
		bool inCheck();

		// Returns a vector of pairs of each possible move that can be made on the Board for the King
		std::vector< std::pair<int, int> > acquireMoves(Board * ChessBoard) override;
		
		~King();

	private:
		bool checked;
		std::pair<int, int> castlingPosition;

		// Handles lateral movement that the King can make on the Board. Adds each possible move as a pair of (row, column) to the 'moves' vector.
		void limitedMobility(Board * ChessBoard);

		// Checks if it is possible to castle, if so includes the move inside the King's possible moves
		void castling(Board * ChessBoard);

		// Checks if there are Enemies that can possibly place the King in Check, if so then changes the boolean 'checked' to be True, false otherwise
		void checkForEnemies(Board * ChessBoard, bool & currentlyChecked);

		// Used in checkForEnemies, has to account for the unique movement of Knights
		void checkForKnights(Board * ChessBoard, bool & currentlyChecked);

	};
};

#endif // KING_H