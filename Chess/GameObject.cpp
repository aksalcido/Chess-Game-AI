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
	: x(piece.x), y(piece.y), color(piece.color), representation(piece.representation), directions(piece.directions)
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

bool Chess::GameObject::validMove(int row, int column, Board * ChessBoard)
{
	moves = acquireMoves(ChessBoard);

	for (std::vector< std::pair<int, int> >::iterator it = moves.begin(); it != moves.end(); ++it)
	{
		if (it->first == row && it->second == column)
			return true;
	}

	return false;
}

bool Chess::GameObject::initialPosition()
{
	return hasNotMoved;
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


std::vector<std::pair<int, int>> Chess::GameObject::adjustMoves(Board * ChessBoard)
{
	std::vector<std::vector<std::pair<int, int>>> enemyPaths = ChessBoard->enemyPaths(color);
	
	std::vector<std::pair<int, int>> path, newMoves;


	//std::cout << "moves.size(): " << moves.size() << std::endl;
	//std::cout << "enemyPaths.size(): " << enemyPaths.size() << std::endl;
	//std::cout << "path.size(): " << path.size() << std::endl;


	// King wants to avoid the Enemies or take them -- also, if there are multiple enemies checking the King, then to avoid a check it is only possible by moving the King
	if (displayPiece() == 'K' || displayPiece() == 'k' || enemyPaths.size() > 1)
	{
		// ??
	}

	// Other GameObjects want to block the Enemies or take them
	else {
		path = enemyPaths.front();

		for (std::vector<std::pair<int, int>>::iterator enemy_it = path.begin(); enemy_it != path.end(); enemy_it++)
		{
			for (std::vector<std::pair<int, int>>::iterator piece_it = moves.begin(); piece_it != moves.end(); piece_it++)
			{
				if (piece_it->first == enemy_it->first && piece_it->second == enemy_it->second)
					newMoves.push_back(std::make_pair(piece_it->first, piece_it->second));
			}
		}
	}
	

	std::cout << "newMoves.size(): " << newMoves.size() << std::endl;

	return newMoves;
}


bool Chess::GameObject::oppositePlayer(int player)
{
	return color != player;
}

bool Chess::GameObject::canAttackEnemy(int enemyRow, int enemyCol, Board * ChessBoard)
{
	moves = acquireMoves(ChessBoard);

	for (std::vector< std::pair<int, int> >::iterator it = moves.begin(); it != moves.end(); ++it)
	{
		if (it->first == enemyRow && it->second == enemyCol)
			return true;
	}

	return false;
}

bool Chess::GameObject::playerInCheck(Board * ChessBoard)
{
	return ChessBoard->kingInCheck(color);
}


void Chess::GameObject::incrementDirection(int & dir)
{
	if (dir != 0)
		dir >= 1 ? dir++ : dir--;
}

Chess::GameObject::~GameObject()
{

}
