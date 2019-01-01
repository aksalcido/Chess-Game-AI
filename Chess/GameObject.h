#pragma once

namespace Chess 
{
	class GameObject
	{
	public:
		
		GameObject();

		GameObject(int newX, int newY, int newColor, char rep);
		
		GameObject(const GameObject & piece);

		GameObject & operator=(const GameObject & piece);

		char displayPiece();
		
		~GameObject();

	private:
		int x;
		int y;
		int color;
		char representation;
	};

	class King : public GameObject
	{
	public:
		King(int newX, int newY, int newColor, char rep);
		~King();
	};

	class Queen : public GameObject
	{
	public:
		Queen(int newX, int newY, int newColor, char rep);
		~Queen();
	};

	class Bishop : public GameObject
	{
	public:
		Bishop(int newX, int newY, int newColor, char rep);
		~Bishop();
	};

	class Knight : public GameObject
	{
	public:
		Knight(int newX, int newY, int newColor, char rep);
		~Knight();
	};

	class Rook : public GameObject
	{
	public:
		Rook(int newX, int newY, int newColor, char rep);
		~Rook();
	};

	class Pawn : public GameObject
	{
	public:
		Pawn(int newX, int newY, int newColor, char rep);
		~Pawn();
	};

	class Square : public GameObject
	{
	public:
		Square(int newX, int newY, int newColor, char rep);

		~Square();

	private:

	};
};