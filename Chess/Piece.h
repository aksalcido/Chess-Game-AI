#pragma once

namespace Chess 
{
	class Piece
	{
	public:
		Piece();
		~Piece();

	private:
		int color;

	};

	class King : public Piece 
	{
	public:
		King();
		~King();
	};

	class Queen : public Piece
	{
	public:
		Queen();
		~Queen();
	};

	class Bishop : public Piece
	{
	public:
		Bishop();
		~Bishop();
	};

	class Knight : public Piece
	{
	public:
		Knight();
		~Knight();
	};

	class Rook : public Piece
	{
	public:
		Rook();
		~Rook();
	};

	class Pawn : public Piece
	{
	public:
		Pawn();
		~Pawn();
	};
};