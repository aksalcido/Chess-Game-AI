#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#pragma once
#include <vector>
#define white 0
#define black 1
#define dimension 8

// Forward Declaration of Board
class Board;

namespace Chess 
{
	struct Direction {
		int dx, dy;
	};

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
		virtual bool validMove(int row, int column, Board * ChessBoard) = 0;

		virtual std::vector< std::pair<int, int> > acquireMoves(Board * ChessBoard) = 0;

		// Returns a pair of the coordinates of the piece
		std::pair<int, int> getCoordinates();

		// Returns the char representation of the piece to display to the user
		char displayPiece();
		
		// Returns an integer representation of the piece color
		int pieceColor();

		// Changes x, y coordinates when piece is moved
		void changeCoordinates(const int row, const int column);

		// Switches the private boolean hasNotMoved to false once the piece makes it's first move
		void firstMoveOccured();

		bool oppositePlayer(int other);

		// Destructor for the GameObject
		~GameObject();

	protected:
		int x, y, color;
		char representation;
		bool hasNotMoved;
		std::vector<Direction> directions;
	};

	class King : public GameObject
	{
	public:
		King(int newX, int newY, int newColor, char rep);

		void move() override;

		bool validMove(int row, int column, Board * ChessBoard) override;

		std::vector< std::pair<int, int> > acquireMoves(Board * ChessBoard) override;

		~King();
	
	private:
		bool inCheck;
	};

	class Queen : public GameObject
	{
	public:
		Queen(int newX, int newY, int newColor, char rep);

		void move() override;

		bool validMove(int row, int column, Board * ChessBoard) override;

		std::vector< std::pair<int, int> > acquireMoves(Board * ChessBoard) override;

		~Queen();
	};

	class Bishop : public GameObject
	{
	public:
		Bishop(int newX, int newY, int newColor, char rep);

		void move() override;

		bool validMove(int row, int column, Board * ChessBoard) override;

		std::vector< std::pair<int, int> > acquireMoves(Board * ChessBoard) override;

		~Bishop();
	};

	class Knight : public GameObject
	{
	public:
		Knight(int newX, int newY, int newColor, char rep);

		void move() override;

		bool validMove(int row, int column, Board * ChessBoard) override;

		std::vector< std::pair<int, int> > acquireMoves(Board * ChessBoard) override;

		void jump(std::vector< std::pair<int, int> > & moves, Board * ChessBoard);

		~Knight();

	};

	class Rook : public GameObject
	{
	public:
		Rook(int newX, int newY, int newColor, char rep);

		void move() override;

		bool validMove(int row, int column, Board * ChessBoard) override;
		
		std::vector< std::pair<int, int> > acquireMoves(Board * ChessBoard) override;

		~Rook();

	};

	class Pawn : public GameObject
	{
	public:
		Pawn(int newX, int newY, int newColor, char rep);

		void move() override;

		// Overrided validMove from base class GameObject, and returns a boolean if the row, column arguments are a valid move on the current Board.
		bool validMove(int row, int column, Board * ChessBoard) override;

		std::vector< std::pair<int, int> > acquireMoves(Board * ChessBoard) override;

		void diagonal(std::vector< std::pair<int, int> > & moves, Board * ChessBoard);

		void forward(std::vector< std::pair<int, int> > & moves, Board * ChessBoard);

		~Pawn();

	private:
		bool enpassant;

	};

};

#endif // GAMEOBJECT_H