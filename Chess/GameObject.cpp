#include "GameObject.h"
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
