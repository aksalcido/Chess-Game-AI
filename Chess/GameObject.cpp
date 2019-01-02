#include "GameObject.h"

// ===== Piece Class ===== //
Chess::GameObject::GameObject()
{

}

Chess::GameObject::GameObject(int newX, int newY, int newColor, char rep) 
	: x(newX), y(newY), color(newColor), representation(rep)
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

bool Chess::GameObject::oppositePlayer(int other)
{
	return color != other;
}

bool Chess::GameObject::emptySpace(int dx, int dy, GameObject(*board[dimension][dimension]))
{
	return board[dx][dy] == nullptr;
}

Chess::GameObject::~GameObject()
{

}

// ===== King Class ===== //
Chess::King::King(int newX, int newY, int newColor, char rep) 
	: hasNotMoved(true), inCheck(false), GameObject(newX, newY, newColor, rep)
{

}

void Chess::King::move()
{

}

bool Chess::King::validMove(int row, int column, GameObject(*board[dimension][dimension]))
{
	return true;
}

std::vector< std::pair<int, int> > Chess::King::acquireMoves(GameObject(*board[dimension][dimension]))
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

}


void Chess::Queen::move()
{

}

bool Chess::Queen::validMove(int row, int column, GameObject(*board[dimension][dimension]))
{
	return true;
}

std::vector< std::pair<int, int> > Chess::Queen::acquireMoves(GameObject(*board[dimension][dimension]))
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

bool Chess::Bishop::validMove(int row, int column, GameObject(*board[dimension][dimension]))
{
	return true;
}

std::vector< std::pair<int, int> > Chess::Bishop::acquireMoves(GameObject(*board[dimension][dimension]))
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

}


void Chess::Knight::move()
{

}

bool Chess::Knight::validMove(int row, int column, GameObject(*board[dimension][dimension]))
{
	return true;
}

std::vector< std::pair<int, int> > Chess::Knight::acquireMoves(GameObject(*board[dimension][dimension]))
{
	std::vector< std::pair<int, int> > moves;




	return moves;
}

Chess::Knight::~Knight()
{

}
// ===== Rook Class ===== //
Chess::Rook::Rook(int newX, int newY, int newColor, char rep) 
	: hasNotMoved(true), GameObject(newX, newY, newColor, rep)
{

}


void Chess::Rook::move()
{

}

bool Chess::Rook::validMove(int row, int column, GameObject(*board[dimension][dimension]))
{
	return true;
}

std::vector< std::pair<int, int> > Chess::Rook::acquireMoves(GameObject(*board[dimension][dimension]))
{
	std::vector< std::pair<int, int> > moves;




	return moves;
}

Chess::Rook::~Rook()
{

}
// ===== Pawn Class ===== //
Chess::Pawn::Pawn(int newX, int newY, int newColor, char rep) 
	: hasNotMoved(true), enpassant(false), GameObject(newX, newY, newColor, rep)
{

}


void Chess::Pawn::move()
{

}

bool Chess::Pawn::validMove(int row, int column, GameObject(*board[dimension][dimension]))
{
	std::vector< std::pair<int, int> > moves = acquireMoves(board);

	for (std::vector< std::pair<int, int> >::iterator it = moves.begin(); it != moves.end(); ++it)
	{
		if (it->first == row && it->second == column)
			return true;
	}

	return false;
}

std::vector< std::pair<int, int> > Chess::Pawn::acquireMoves(GameObject(*board[dimension][dimension]))
{
	std::vector< std::pair<int, int> > moves;

	forward(moves, board);
	diagonal(moves, board);

	return moves;
}

void Chess::Pawn::forward(std::vector< std::pair<int, int> > & moves, GameObject(*board[dimension][dimension]))
{
	int dx = (color == white ? -1 : 1);

	// If Pawn has not moved yet, then capable of moving up two spaces
	if (hasNotMoved && emptySpace(x + 2 * dx, y, board))
	{
		moves.push_back(std::make_pair(x + 2 * dx, y));
	}

	// Pawn can also move up one space as long as the space is not occupied
	if (emptySpace(x + 1 * dx, y, board))
	{
		moves.push_back(std::make_pair(x + 1 * dx, y));
	}
}

void Chess::Pawn::diagonal(std::vector< std::pair<int, int> > & moves, GameObject(*board[dimension][dimension]))
{
	int dx = x + (color == white ? -1 : 1);

	// If the space is not empty and is occupied by an enemy, then it is possible for the Pawn to move there
	if (!emptySpace(dx, y - 1, board) && oppositePlayer(board[dx][y - 1] -> pieceColor() ))
	{
		moves.push_back(std::make_pair(dx, y - 1));
	}

	if (!emptySpace(dx, y + 1, board) && oppositePlayer(board[dx][y + 1] -> pieceColor() ))
	{
		moves.push_back(std::make_pair(dx, y + 1));
	}
}


Chess::Pawn::~Pawn()
{

}