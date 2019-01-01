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

Chess::GameObject::~GameObject()
{

}

// King Class //
Chess::King::King(int newX, int newY, int newColor, char rep) : GameObject(newX, newY, newColor, rep)
{

}

Chess::King::~King()
{

}
// Queen Class //
Chess::Queen::Queen(int newX, int newY, int newColor, char rep) : GameObject(newX, newY, newColor, rep)
{

}

Chess::Queen::~Queen()
{

}
// Bishop Class //
Chess::Bishop::Bishop(int newX, int newY, int newColor, char rep) : GameObject(newX, newY, newColor, rep)
{

}

Chess::Bishop::~Bishop()
{

}
// Knight Class //
Chess::Knight::Knight(int newX, int newY, int newColor, char rep) : GameObject(newX, newY, newColor, rep)
{

}

Chess::Knight::~Knight()
{

}
// Rook Class //
Chess::Rook::Rook(int newX, int newY, int newColor, char rep) : GameObject(newX, newY, newColor, rep)
{

}

Chess::Rook::~Rook()
{

}
// Pawn Class //
Chess::Pawn::Pawn(int newX, int newY, int newColor, char rep) : GameObject(newX, newY, newColor, rep)
{

}

Chess::Pawn::~Pawn()
{

}

// Square Class //
Chess::Square::Square(int newX, int newY, int newColor, char rep) : GameObject(newX, newY, newColor, rep)
{

}

Chess::Square::~Square()
{

}