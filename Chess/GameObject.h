#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#pragma once
#include <vector>
#include "Direction.h"
#define white 0
#define black 1
#define dimension 8

namespace Chess 
{
	// Forward Declaration of Board
	class Board;

	class GameObject
	{
	public:
		
		// Default Constructor for the GameObject 
		GameObject();

		// Constructor for the GameObject which takes a x, y coordinate with the color and character representation
		GameObject(int newX, int newY, int newColor, char rep);
		
		// Copy constructor
		GameObject(const GameObject & piece);

		// Overloaded = operator for cases where GameObject is copied 
		GameObject & operator=(const GameObject & piece);
		
		// Virtual function used on any of the piece GameObjects on the board since they all have different movement patterns
		virtual std::vector< std::pair<int, int> > acquireMoves(Board * ChessBoard) = 0;

		// Adjusts the moves to be applicable for the King being in Check
		std::vector<std::pair<int, int>> adjustMoves(Board * ChessBoard);

		// Returns a pair of the coordinates of the GameObject
		std::pair<int, int> getCoordinates();

		// Receives coordinates and the Board and returns a boolean if the move is valid. False otherwise
		bool validMove(int row, int column, Board * ChessBoard);

		// Returns a boolean True if a GameObject has not been moved yet, otherwise False
		bool initialPosition();

		// Returns the char representation of the piece to display to the user
		char displayPiece();
		
		// Returns an integer representation of the piece color. 0 - white / 1 - black.
		int pieceColor();

		// Updates the x, y coordinates of the GameObject to the arguments (row, column)
		void changeCoordinates(const int row, const int column);

		// Switches the private boolean hasNotMoved to false once the GameObject has made its first move
		void firstMoveOccured();

		// Increments the integer representation of the Direction on the 2d board by whichever direction it is going to continue the search
		void incrementDirection(int & dir);

		// Returns a Boolean True if the argument player is the opposite player of the GameObject calling this function
		bool oppositePlayer(int player);

		// Returns a Boolean True if the GameObject calling this function is capable of attacking coordinates (enemyRow, enemyCol). False otherwise
		bool canAttackEnemy(int enemyRow, int enemyCol, Board * ChessBoard);
		
		// Returns a Boolean True if the GameObject calling this function has their King in check
		bool playerInCheck(Board * ChessBoard);

		// Destructor for the GameObject
		~GameObject();

	protected:
		int x, y, color;
		char representation;
		bool hasNotMoved;
		std::vector<Direction> directions;
		std::vector<std::pair<int, int>> moves;

	};
};

#include "Board.h"
#endif // GAMEOBJECT_H