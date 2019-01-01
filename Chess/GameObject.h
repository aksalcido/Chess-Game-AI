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

		virtual std::vector< std::pair<int, int> > acquireMoves() = 0;

		// Returns the char representation of the piece to display to the user
		char displayPiece();
		
		// Returns an integer representation of the piece color
		int pieceColor();

		// Changes x, y coordinates when piece is moved
		void changeCoordinates(const int row, const int column);


		// Destructor for the GameObject
		~GameObject();

	private:
		int x, y, color;
		char representation;

	};

	class King : public GameObject
	{
	public:
		King(int newX, int newY, int newColor, char rep);

		void move() override;

		bool validMove(int row, int column, GameObject(*board[dimension][dimension])) override;

		std::vector< std::pair<int, int> > acquireMoves() override;

		~King();
	
	private:
		bool untouched, inCheck;
	};

	class Queen : public GameObject
	{
	public:
		Queen(int newX, int newY, int newColor, char rep);

		void move() override;

		bool validMove(int row, int column, GameObject(*board[dimension][dimension])) override;

		std::vector< std::pair<int, int> > acquireMoves() override;

		~Queen();
	};

	class Bishop : public GameObject
	{
	public:
		Bishop(int newX, int newY, int newColor, char rep);

		void move() override;

		bool validMove(int row, int column, GameObject(*board[dimension][dimension])) override;

		std::vector< std::pair<int, int> > acquireMoves() override;

		~Bishop();
	};

	class Knight : public GameObject
	{
	public:
		Knight(int newX, int newY, int newColor, char rep);

		void move() override;

		bool validMove(int row, int column, GameObject(*board[dimension][dimension])) override;

		std::vector< std::pair<int, int> > acquireMoves() override;

		~Knight();
	};

	class Rook : public GameObject
	{
	public:
		Rook(int newX, int newY, int newColor, char rep);

		void move() override;

		bool validMove(int row, int column, GameObject(*board[dimension][dimension])) override;
		
		std::vector< std::pair<int, int> > acquireMoves() override;

		~Rook();
	private:
		bool untouched;

	};

	class Pawn : public GameObject
	{
	public:
		Pawn(int newX, int newY, int newColor, char rep);

		void move() override;

		bool validMove(int row, int column, GameObject(*board[dimension][dimension])) override;

		std::vector< std::pair<int, int> > acquireMoves() override;

		~Pawn();

	private:
		bool untouched, enpassant;

	};

};
#endif // GAMEOBJECT_H