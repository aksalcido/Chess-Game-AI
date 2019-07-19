#include "ChessAI.h"

Chess::ChessAI::ChessAI() : color(black)
{

}

Move Chess::ChessAI::chooseMove(Board * ChessBoard)
{
	if (difficulty == EASY)
		return easyMove(ChessBoard);

	else if (difficulty == NORMAL)
		return normalMove(ChessBoard);

}

#include <iostream>

Move Chess::ChessAI::easyMove(Board * ChessBoard)
{
	GameObjectMoves moveMap = ChessBoard->allMoves(color);
	GameObjectMoves::iterator it;
	int random_piece, random_move, index = 0;

	std::pair<int, int> coordinates, move;

	std::default_random_engine engine{ device() };

	// Determines the random piece that will be chosen
	std::uniform_int_distribution<int> pieceDistribution(0, moveMap.size() - 1);
	random_piece = pieceDistribution(engine);

	// Since we do not know the key at the random_piece, we have to iterate through until our index is the value of random_piece and then save the key 'coordinates.'
	for (it = moveMap.begin(); it != moveMap.end(); it++, index++)
	{
		if (index == random_piece) {
			coordinates = it->first;
			break;
		}
	}

	// Determines the random move that will be chosen in that piece
	std::uniform_int_distribution<int> moveDistribution(0, it->second.size() - 1);
	random_move = moveDistribution(engine);

	// We are now iterating through the Moves vector of the GameObject
	move = it->second[random_move];

	std::cout << "Movemap.Size(): " << moveMap.size() << " random_piece: " << random_piece << " moves.size(): " << it->second.size() << " random_move: " << random_move << std::endl;

	return Move{ coordinates, move };
}

Move Chess::ChessAI::normalMove(Board * ChessBoard)
{
	return Move{ std::pair<int, int>{ 0, 0 }, std::pair<int, int>{ 0, 0 } };
}

void Chess::ChessAI::setDifficulty(int newDifficulty)
{
	difficulty = newDifficulty;
}

Chess::ChessAI::~ChessAI()
{

}
