#ifndef BOARD_H
#define BOARD_H
#pragma once
#include <memory>
#include "GameObject.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

#define QUEEN_PROMOTION 1
#define ROOK_PROMOTION 2
#define BISHOP_PROMOTION 3
#define KNIGHT_PROMOTION 4

namespace Chess {

	class Board
	{
	public:
		// Initializes a Board object that contains the GameObject pieces that are on the board during play
		Board();

		// Board copy constructor used when cloning a Board object
		Board(const Board & b);

		// movementToEmptySquare() simply swaps a GameObject with the nullptr held in the endRow, endCol coordinates
		void movementToEmptySquare(int row, int col, int endRow, int endCol);

		// movementToEnemy() occurs when the piece is moving onto an occupied (by enemy) square. Differs from movement
		// to a normal square, because memory deallocation is required when removing a GameObject from the board
		void movementToEnemy(int row, int col, int endRow, int endCol);

		// Called after a GameObject has been moved on the board and updates the coordinates of a the GameObject to the arguments (newRow, newCol)
		void updateCoordinates(int newRow, int newCol);

		// Checks if the GameObject at coordinates (row, col) has moved, if so changes the boolean hasNotMoved for that piece to false
		void firstMoveCheck(int row, int col);

		// Checks if castling has been requested during the turn using argument (row, col) which must be a King GameObject. And if castling is
		// possible, proceeds to swap the Rook and King in respects to the Chess Castling Rule
		void castlingCheck(int row, int col);

		// Checks if the Game is complete at the end of a turn, if so raises a GameOverException that is caught in the GameState
		void gameFinishedCheck(int turn, bool currentlyChecked);

		// Checks if either Kings for both players is in Check after a turn has been made
		void playerStatus();
		
		// Handles the promotion once received the user inputted argument 'promoted' on which piece they want
		void promote(int row, int col, int promoted);

		// Checks if a pawn has reached the end of the board for the respective player, if so then promotion is forced which requires user input so we pass the GameState pointer
		bool promotion(int row, int col);

		// Returns a boolean True if a GameObject at coordinates (row, col) has not been moved on the board. False otherwise
		bool pieceHasNotMoved(int row, int col);

		// Returns a boolean True if the move from coordinates (row, col) -> (endRow, endCol) is a valid move that can be made. False otherwise
		bool validMove(int row, int col, int endRow, int endCol);

		// Returns a boolean True if the move is safe in regards to the King not being in check after making the move from (row, col) -> (endRow, endCol). False otherwise
		bool safeMove(int row, int col, int endRow, int endCol);

		// Returns a boolean True if the coordinates (row, col) are an empty space on the board. False otherwise
		bool emptySpace(int row, int col) const;

		// Returns a boolean True if the coordinates (dx, dy) is an enemy GameObject to the GameObject at coordinates (row, col)
		bool enemySpace(int row, int col, int dx, int dy) const;

		// Returns a boolean True if the enemy at coordinates (enemyRow, enemyCol) is able to move to coordinates of the king -- hence placing the King in Check
		bool enemyCheckingKing(int enemyRow, int enemyCol, int kingRow, int kingCol);

		// Returnsa boolean True if the row and column argument remain in bounds on the board. False otherwise
		bool inBounds(int row, int col) const;

		// Returns a Boolean True if the argument 'color' representing the Player has their King in check
		bool kingInCheck(int color) const;

		// Returns the char representation of the piece at coordinate (row, col) on the board
		char piece(int row, int col) const;

		// Returns the int representation of the color of the piece at coordinate (row, col) on the board
		int pieceColor(int row, int col) const;

		// Returns a Vector of the Moves for each GameObject that takes a Path to check the King GameObject
		// The Vector length will represent how many GameObjects are checking the King, so typically it will be of length 1, any higher will
		// mean that there are multiple GameObjects checking the King and then only the King is capable of movement. If no movement, then Player is in checkmate
		std::vector<Moves> enemyPaths(int color);

		// Returns a unique_ptr of the current Board state that will be deallocated naturally when not needed anymore
		// Useful for possibilities of including AI and checking if the King is in checkmate
		std::unique_ptr<Board> clone();

		// Destructor for the Board Object, releases left over pieces that remain on the board after game is over
		~Board();

	private:
		GameObject * board[dimension][dimension];

		// Updates the pieces vectors stored in the Board object by removing the GameObject argument
		void updatePieces(GameObject * pieceBeingRemoved);

		// Initializes the Board to contain GameObject pieces similar to the char representation of the Board, This allows the board
		// to become fully accessible game objects that allow the game to progress, rather than simply using char types.
		void initialize(GameObject(*board[dimension][dimension]));
		
		// Copies the otherBoard argument and dynamically allocates GamePieces to accomdate the different state of the otherBoard
		// Necessary for the function 'clone' and returning a unique_ptr of the board
		void copy(const Board & otherBoard);

		// 2 Vectors needed to hold all of the GameObject pieces for each player
		std::vector<GameObject*> whitePieces, blackPieces;

		// 2 GameObjects needed to keep track of the King for each player -- most important piece on the Board
		GameObject * whiteKing, * blackKing;
	};
};

#endif // BOARD_H