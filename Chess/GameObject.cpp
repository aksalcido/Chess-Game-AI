#include "GameObject.h"

// ===== Piece Class ===== //
Chess::GameObject::GameObject()
{

}

Chess::GameObject::GameObject(int newX, int newY, int newColor, char rep) : x(newX), y(newY), color(newColor), representation(rep)
{

}

// Copy Constructor //
Chess::GameObject::GameObject(const GameObject & piece) : x(piece.x), y(piece.y), color(piece.color), representation(piece.representation)
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

Chess::GameObject::~GameObject()
{

}

// ===== King Class ===== //
Chess::King::King(int newX, int newY, int newColor, char rep) : untouched(true), inCheck(false), GameObject(newX, newY, newColor, rep)
{

}

void Chess::King::move()
{

}

bool Chess::King::validMove(const int row, const int column, GameObject(*board[dimension][dimension]))
{
	return true;
}

Chess::King::~King()
{

}
// ===== Queen Class ===== //
Chess::Queen::Queen(int newX, int newY, int newColor, char rep) : GameObject(newX, newY, newColor, rep)
{

}


void Chess::Queen::move()
{

}

bool Chess::Queen::validMove(const int row, const int column, GameObject(*board[dimension][dimension]))
{
	return true;
}

Chess::Queen::~Queen()
{

}
// ===== Bishop Class ===== //
Chess::Bishop::Bishop(int newX, int newY, int newColor, char rep) : GameObject(newX, newY, newColor, rep)
{

}


void Chess::Bishop::move()
{

}

bool Chess::Bishop::validMove(const int row, const int column, GameObject(*board[dimension][dimension]))
{
	return true;
}

Chess::Bishop::~Bishop()
{

}
// ===== Knight Class ===== //
Chess::Knight::Knight(int newX, int newY, int newColor, char rep) : GameObject(newX, newY, newColor, rep)
{

}


void Chess::Knight::move()
{

}

bool Chess::Knight::validMove(const int row, const int column, GameObject(*board[dimension][dimension]))
{
	return true;
}

Chess::Knight::~Knight()
{

}
// ===== Rook Class ===== //
Chess::Rook::Rook(int newX, int newY, int newColor, char rep) : untouched(true), GameObject(newX, newY, newColor, rep)
{

}


void Chess::Rook::move()
{

}

bool Chess::Rook::validMove(const int row, const int column, GameObject(*board[dimension][dimension]))
{
	return true;
}

Chess::Rook::~Rook()
{

}
// ===== Pawn Class ===== //
Chess::Pawn::Pawn(int newX, int newY, int newColor, char rep) : untouched(true), enpassant(false), GameObject(newX, newY, newColor, rep)
{

}


void Chess::Pawn::move()
{

}

bool Chess::Pawn::validMove(const int row, const int column, GameObject(*board[dimension][dimension]))
{
	// If Pawn hasn't been moved, then is able to jump 2 squares
	

	return true;
}

Chess::Pawn::~Pawn()
{

}