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

		virtual std::vector< std::pair<int, int> > acquireMoves(Board * ChessBoard) = 0;

		// Receives coordinates and the Board and returns a boolean if the move is valid. False otherwise
		bool validMove(int row, int column, Board * ChessBoard);

		// Returns a pair of the coordinates of the piece
		std::pair<int, int> getCoordinates();

		// Returns a boolean True if a GameObject has not been moved yet, otherwise False
		bool initialPosition();

		// Returns the char representation of the piece to display to the user
		char displayPiece();
		
		// Returns an integer representation of the piece color
		int pieceColor();

		// Changes x, y coordinates when piece is moved
		void changeCoordinates(const int row, const int column);

		// Switches the private boolean hasNotMoved to false once the piece makes it's first move
		void firstMoveOccured();

		// Returns a Boolean True if the argument player is the opposite player of the current player's turn
		bool oppositePlayer(int player);

		bool canAttackEnemy(int enemyRow, int enemyCol, Board * ChessBoard);

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