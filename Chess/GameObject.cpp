#include "GameObject.h"
#include "Board.h"
#include <iostream>

// ===== Piece Class ===== //
Chess::GameObject::GameObject()
{

}

Chess::GameObject::GameObject(int newX, int newY, int newColor, char rep) 
	: x(newX), y(newY), color(newColor), representation(rep), hasNotMoved(true)
{

}

// Copy Constructor //
Chess::GameObject::GameObject(const GameObject & piece) 
	: x(piece.x), y(piece.y), color(piece.color), representation(piece.representation)
{

}

Chess::GameObject& Chess::GameObject::operator=(const Chess::GameObject & piece)
{
	x = piece.x;
	y = piece.y;
	color = piece.color;
	representation = piece.representation;

	return *this;
}

std::pair<int, int> Chess::GameObject::getCoordinates()
{
	return std::make_pair(x, y);
}

char Chess::GameObject::displayPiece()
{
	return representation;
}

int Chess::GameObject::pieceColor()
{
	return color;
}

void Chess::GameObject::changeCoordinates(const int row, const int column)
{
	x = row;
	y = column;
}

void Chess::GameObject::firstMoveOccured()
{
	if (hasNotMoved)
		hasNotMoved = false;
}

bool Chess::GameObject::oppositePlayer(int other)
{
	return color != other;
}


Chess::GameObject::~GameObject()
{

}

// ===== King Class ===== //
Chess::King::King(int newX, int newY, int newColor, char rep) 
	: inCheck(false), GameObject(newX, newY, newColor, rep)
{
	directions = std::vector<Direction>
	{
		Direction{ 1, 1 }, Direction{ 1, 0 }, Direction{ 0, 1 }, Direction{ -1, -1 },
		Direction{ -1, 0 }, Direction{ -1, 1 }, Direction{ 1, -1 }, Direction{ 0, -1 }
	};

}

void Chess::King::move()
{

}

bool Chess::King::validMove(int row, int column, Board * ChessBoard)
{
	return true;
}

std::vector< std::pair<int, int> > Chess::King::acquireMoves(Board * ChessBoard)
{
	std::vector< std::pair<int, int> > moves;




	return moves;
}


Chess::King::~King()
{

}
// ===== Queen Class ===== //
Chess::Queen::Queen(int newX, int newY, int newColor, char rep) 
	: GameObject(newX, newY, newColor, rep)
{
	directions = std::vector<Direction>{ 
		Direction{ 1, 1 }, Direction{ 1, 0 }, Direction{ 0, 1 }, Direction{ -1, -1 },
		Direction{ -1, 0 }, Direction{ -1, 1 }, Direction{ 1, -1 }, Direction{ 0, -1 }
	};

}


void Chess::Queen::move()
{

}

bool Chess::Queen::validMove(int row, int column, Board * ChessBoard)
{
	return true;
}

std::vector< std::pair<int, int> > Chess::Queen::acquireMoves(Board * ChessBoard)
{
	std::vector< std::pair<int, int> > moves;




	return moves;
}

Chess::Queen::~Queen()
{

}
// ===== Bishop Class ===== //
Chess::Bishop::Bishop(int newX, int newY, int newColor, char rep) 
	: GameObject(newX, newY, newColor, rep)
{

}


void Chess::Bishop::move()
{

}

bool Chess::Bishop::validMove(int row, int column, Board * ChessBoard)
{
	return true;
}

std::vector< std::pair<int, int> > Chess::Bishop::acquireMoves(Board * ChessBoard)
{
	std::vector< std::pair<int, int> > moves;




	return moves;
}

Chess::Bishop::~Bishop()
{

}
// ===== Knight Class ===== //
Chess::Knight::Knight(int newX, int newY, int newColor, char rep) 
	: GameObject(newX, newY, newColor, rep)
{
	directions = std::vector<Direction>{
		Direction{ 1, 2 }, Direction{ 1, -2 }, Direction{ -1, 2 }, Direction{ -1, -2 },
		Direction{ 2, 1 }, Direction{ 2, -1 }, Direction{ -2, 1 }, Direction{ -2, -1 }
	};
}


void Chess::Knight::move()
{

}

bool Chess::Knight::validMove(int row, int column, Board * ChessBoard)
{
	std::vector< std::pair<int, int> > moves = acquireMoves(ChessBoard);

	for (std::vector< std::pair<int, int> >::iterator it = moves.begin(); it != moves.end(); ++it)
	{
		if (it->first == row && it->second == column)
			return true;
	}

	return false;
}

std::vector< std::pair<int, int> > Chess::Knight::acquireMoves(Board * ChessBoard)
{
	std::vector< std::pair<int, int> > moves;
	jump(moves, ChessBoard);

	return moves;
}

void Chess::Knight::jump(std::vector< std::pair<int, int> > & moves, Board * ChessBoard)
{	
	int dx, dy;

	for (int i = 0; i < directions.size(); i++)
	{
		dx = directions[i].dx;
		dy = directions[i].dy;

		if (ChessBoard->emptySpace(x + dx, y + dy) || ChessBoard->enemySpace(x, y, x + dx, y + dy))
		{
			moves.push_back(std::make_pair(x + dx, y + dy));
		}

	}
}

Chess::Knight::~Knight()
{

}
// ===== Rook Class ===== //
Chess::Rook::Rook(int newX, int newY, int newColor, char rep) 
	: GameObject(newX, newY, newColor, rep)
{

}

void Chess::Rook::move()
{

}

bool Chess::Rook::validMove(int row, int column, Board * ChessBoard)
{
	std::vector< std::pair<int, int> > moves = acquireMoves(ChessBoard);

	for (std::vector< std::pair<int, int> >::iterator it = moves.begin(); it != moves.end(); ++it)
	{
		if (it->first == row && it->second == column)
			return true;
	}

	return false;
}

std::vector< std::pair<int, int> > Chess::Rook::acquireMoves(Board * ChessBoard)
{
	std::vector< std::pair<int, int> > moves;


	return moves;
}

Chess::Rook::~Rook()
{

}

// ===== Pawn Class ===== //
Chess::Pawn::Pawn(int newX, int newY, int newColor, char rep) 
	: enpassant(false), GameObject(newX, newY, newColor, rep)
{

}


void Chess::Pawn::move()
{

}

bool Chess::Pawn::validMove(int row, int column, Board * ChessBoard)
{
	std::vector< std::pair<int, int> > moves = acquireMoves(ChessBoard);

	for (std::vector< std::pair<int, int> >::iterator it = moves.begin(); it != moves.end(); ++it)
	{
		if (it->first == row && it->second == column)
			return true;
	}

	return false;
}

std::vector< std::pair<int, int> > Chess::Pawn::acquireMoves(Board * ChessBoard)
{
	std::vector< std::pair<int, int> > moves;

	forward(moves, ChessBoard);
	diagonal(moves, ChessBoard);

	return moves;
}

void Chess::Pawn::forward(std::vector< std::pair<int, int> > & moves, Board * ChessBoard)
{
	int dx = (color == white ? -1 : 1);

	// If Pawn has not moved yet, then capable of moving up two spaces
	if (hasNotMoved && ChessBoard -> emptySpace(x + 2 * dx, y))
	{
		moves.push_back(std::make_pair(x + 2 * dx, y));
	}

	// Pawn can also move up one space as long as the space is not occupied
	if (ChessBoard -> emptySpace(x + 1 * dx, y))
	{
		moves.push_back(std::make_pair(x + 1 * dx, y));
	}
}

void Chess::Pawn::diagonal(std::vector< std::pair<int, int> > & moves, Board * ChessBoard)
{
	int dx = x + (color == white ? -1 : 1);

	// If the space is not empty and is occupied by an enemy, then it is possible for the Pawn to move there
	//if (!ChessBoard -> emptySpace(dx, y - 1) && oppositePlayer(ChessBoard -> pieceColor(dx, y-1)))
	if ( ChessBoard -> enemySpace(x, y, dx, y-1) )
	{
		moves.push_back(std::make_pair(dx, y - 1));
	}

	//if (!ChessBoard -> emptySpace(dx, y + 1) && oppositePlayer(ChessBoard -> pieceColor(dx, y + 1)))
	if ( ChessBoard -> enemySpace(x, y, dx, y + 1) )
	{
		moves.push_back(std::make_pair(dx, y + 1));
	}
}


Chess::Pawn::~Pawn()
{

}