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

		// Checks if the piece has moved, if so changes the boolean hasNotMoved for that piece to false
		void firstMoveCheck(int row, int col);

		// Checks if castling has been requested during the turn, and if possible swaps the rook and king in respects to the Chess Castling Rule
		void castlingCheck(int row, int col);

		// Checks if either Kings are in Check after each turn
		void playerStatus(int turn);

		// Returns a boolean True if a GameObject given (row, col) argument has been moved throughout the Game. False otherwise
		bool pieceHasNotMoved(int row, int col);

		// Returns a boolean True if the move from start -> end is a valid move that can be made. False otherwise
		bool validMove(int row, int col, int endRow, int endCol);

		// Returns a boolean True if the coordinates (row, col) are an empty space on the board. False otherwise
		bool emptySpace(int row, int col) const;

		// Returns a boolean True if the coordinates (dx, dy) are an enemy in comparison to the GameObject at coordinates (row, col)
		bool enemySpace(int row, int col, int dx, int dy) const;

		// Returns a boolean True if the enemy at coordinates (enemyRow, enemyCol) is able to move to coordinates of the king -- hence placing the King in Check
		bool enemyCheckingKing(int enemyRow, int enemyCol, int kingRow, int kingCol);

		// Returnsa boolean True if the row and column argument remain in bounds on the board. False otherwise
		bool inBounds(int row, int col) const;

		// Returns the char representation of the piece at coordinate (row, col) on the board
		char piece(int row, int col) const;

		// Returns the int representation of the color of the piece at coordinate (row, col) on the board
		int pieceColor(int row, int col) const;

		std::vector< std::pair<int, int> > allMoves(int color);

		void updatePieces(GameObject * pieceBeingRemoved);

		// Destructor for the Board Object, releases left over pieces that remain on the board after game is over
		~Board();

	private:
		GameObject * board[dimension][dimension];

		// Initializes the Board to contain GameObject pieces similar to the char representation of the Board, This allows the board
		// to become fully accessible game objects that allow the game to progress, rather than simply using char types.
		void initialize(GameObject(*board[dimension][dimension]));

		// 2 Vectors needed to hold all of the GameObject pieces for each player
		std::vector<GameObject*> whitePieces, blackPieces;

		// 2 GameObjects needed to keep track of the King for each player -- most important piece on the Board
		GameObject * whiteKing, * blackKing;
	};
};

#endif // BOARD_H