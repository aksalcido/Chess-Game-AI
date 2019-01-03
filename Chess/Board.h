#ifndef BOARD_H
#define BOARD_H
#pragma once
#include "GameObject.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

namespace Chess {
	class Board
	{
	public:
		// Initializes a Board object that contains the GameObject pieces that are on the board during play
		Board();

		// movementToEmptySquare() simply swaps a GameObject with the nullptr held in the endRow, endCol coordinates
		void movementToEmptySquare(int row, int col, int endRow, int endCol);

		// movementToEnemy() occurs when the piece is moving onto an occupied (by enemy) square. Differs from movement
		// to a normal square, because memory deallocation is required when removing a GameObject from the board
		void movementToEnemy(int row, int col, int endRow, int endCol);

		// Updates the coordinates of a newly moved piece to the arguments newRow and newCol
		void updateCoordinates(int newRow, int newCol);

		void firstMoveCheck(int row, int col);

		// Returns a boolean True if the move from start -> end is a valid move that can be made. False otherwise
		bool validMove(int row, int col, int endRow, int endCol);

		// Returns the char representation of the piece at coordinate x and y on the board
		char piece(int x, int y) const;

		// Returns the int representation of the color of the piece at coordinate x and y on the board
		int pieceColor(int x, int y) const;

		// Returns a boolean True if the coordinates dx, dy are an empty space on the board. False otherwise
		bool emptySpace(int dx, int dy) const;

		bool enemySpace(int row, int col, int dx, int dy) const;

		// Returnsa boolean True if the row and column argument remain in bounds on the board. False otherwise
		bool inBounds(int row, int column) const;

		// Destructor for the Board Object, releases left over pieces that remain on the board after game is over
		~Board();

	private:
		GameObject * board[dimension][dimension];

		// Initializes the Board to contain GameObject pieces similar to the char representation of the Board, This allows the board
		// to become fully accessible game objects that allow the game to progress, rather than simply using char types.
		void initialize(GameObject(*board[dimension][dimension]));

	};
};

#endif // BOARD_H