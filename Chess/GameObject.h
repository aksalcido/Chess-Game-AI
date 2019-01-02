#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#pragma once
#include <vector>

#define white 0
#define black 1
#define dimension 8

namespace Chess 
{
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

		virtual void move() = 0;
		
		// Receives coordinates and the Board and returns a boolean if the move is valid. False otherwise
		virtual bool validMove(int row, int column, GameObject(*board[dimension][dimension])) = 0;

		virtual std::vector< std::pair<int, int> > acquireMoves(GameObject(*board[dimension][dimension])) = 0;

		// Returns the char representation of the piece to display to the user
		char displayPiece();
		
		// Returns an integer representation of the piece color
		int pieceColor();

		// Changes x, y coordinates when piece is moved
		void changeCoordinates(const int row, const int column);

		bool oppositePlayer(int other);

		bool emptySpace(int dx, int dy, GameObject(*board[dimension][dimension]));

		// Destructor for the GameObject
		~GameObject();

	protected:
		int x, y, color;
		char representation;

	};

	class King : public GameObject
	{
	public:
		King(int newX, int newY, int newColor, char rep);

		void move() override;

		bool validMove(int row, int column, GameObject(*board[dimension][dimension])) override;

		std::vector< std::pair<int, int> > acquireMoves(GameObject(*board[dimension][dimension])) override;

		~King();
	
	private:
		bool hasNotMoved, inCheck;
	};

	class Queen : public GameObject
	{
	public:
		Queen(int newX, int newY, int newColor, char rep);

		void move() override;

		bool validMove(int row, int column, GameObject(*board[dimension][dimension])) override;

		std::vector< std::pair<int, int> > acquireMoves(GameObject(*board[dimension][dimension])) override;

		~Queen();
	};

	class Bishop : public GameObject
	{
	public:
		Bishop(int newX, int newY, int newColor, char rep);

		void move() override;

		bool validMove(int row, int column, GameObject(*board[dimension][dimension])) override;

		std::vector< std::pair<int, int> > acquireMoves(GameObject(*board[dimension][dimension])) override;

		~Bishop();
	};

	class Knight : public GameObject
	{
	public:
		Knight(int newX, int newY, int newColor, char rep);

		void move() override;

		bool validMove(int row, int column, GameObject(*board[dimension][dimension])) override;

		std::vector< std::pair<int, int> > acquireMoves(GameObject(*board[dimension][dimension])) override;

		~Knight();
	};

	class Rook : public GameObject
	{
	public:
		Rook(int newX, int newY, int newColor, char rep);

		void move() override;

		bool validMove(int row, int column, GameObject(*board[dimension][dimension])) override;
		
		std::vector< std::pair<int, int> > acquireMoves(GameObject(*board[dimension][dimension])) override;

		~Rook();
	private:
		bool hasNotMoved;

	};

	class Pawn : public GameObject
	{
	public:
		Pawn(int newX, int newY, int newColor, char rep);

		void move() override;

		bool validMove(int row, int column, GameObject(*board[dimension][dimension])) override;

		std::vector< std::pair<int, int> > acquireMoves(GameObject(*board[dimension][dimension])) override;

		void diagonal(std::vector< std::pair<int, int> > & moves, GameObject(*board[dimension][dimension]));

		void forward(std::vector< std::pair<int, int> > & moves, GameObject(*board[dimension][dimension]));

		~Pawn();

	private:
		bool hasNotMoved, enpassant;

	};

};
#endif // GAMEOBJECT_H