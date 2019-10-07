#include "ChessAI.h"

Chess::ChessAI::ChessAI() : color(black)
{

}

void Chess::ChessAI::setDifficulty(int newDifficulty)
{
	difficulty = newDifficulty;
}

Move Chess::ChessAI::chooseMove(Board * ChessBoard)
{
	if (difficulty == EASY)
		return easyMove(ChessBoard);

	else if (difficulty == NORMAL)
		return normalMove(ChessBoard);

}


#include <iostream>

GameObjectMoves Chess::ChessAI::removeUnmovablePieces(GameObjectMoves & moveMap)
{
	GameObjectMoves newMap;

	for (GameObjectMoves::iterator it = moveMap.begin(); it != moveMap.end(); it++)
	{
		if (it->second.size() != 0)
			newMap.insert(std::make_pair(it->first, it->second));
	}

	return newMap;
}

typedef std::vector<std::pair<int, int>> Moves;
typedef std::map<std::pair<int, int>, Moves> GameObjectMoves;

Move Chess::ChessAI::easyMove(Board * ChessBoard)
{
	// Initializes a tempMap of all pieces and then discards the pieces that have no available moves on the Chessboard
	GameObjectMoves tempMap = ChessBoard->allMoves(color), moveMap = removeUnmovablePieces(tempMap);
		
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

	return Move{ coordinates, move };
}

#include <iostream>

Move Chess::ChessAI::normalMove(Board * ChessBoard)
{
	std::map<int, Move> moveMap;
	int minmax = search(MAX_DEPTH, *ChessBoard, moveMap, 0, black, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
	std::cout << "minmax: " << minmax << std::endl;

	return moveMap[minmax];
}

int Chess::ChessAI::search(int depth, const Board & ChessBoard, std::map<int, Move> & moveMap, int bonus, int turn, int alpha, int beta)
{
	if (depth == 0) {
		return evaluate(ChessBoard, bonus);
	}

	int minmax, moveScore = 0, moveBonus = 0;
	int nextTurn = (turn == black ? white : black);
	GameObjectMoves allMoves;
	std::pair<int, int> coordinates, endCoordinates;

	// Player's Turn -- White Player
	if (turn == white)
	{
		// Absolute min() value for an integer to store is necessary for the Player's Turn
		minmax = std::numeric_limits<int>::min();
		allMoves = ChessBoard.allMoves(white);
		
		for (GameObjectMoves::iterator it = allMoves.begin(); it != allMoves.end(); it++)
		{
			// These Coordinates represent the GameObject we are going to move
			coordinates = it->first;

			for (unsigned int i = 0; i < it->second.size(); i++)
			{
				std::unique_ptr<Board> copy = ChessBoard.clone();
				endCoordinates = it->second[i];
				copy->minmaxUpdate(coordinates, endCoordinates);

				// minmaxUpdate does not guarantee that there won't be a move that puts the Player's King in check, if so then we just disregard it by only accepting valid boards
				if (!copy->kingInCheck(white)) {
					moveBonus = bonus + bonusPoints(endCoordinates.first, endCoordinates.second, copy->piece(endCoordinates.first, endCoordinates.second));
					minmax = std::max(minmax, search(depth - 1, *copy, moveMap, moveBonus, nextTurn, alpha, beta));

					alpha = std::max(alpha, minmax);

					if (alpha >= beta)
						break; // Beta cut-off
				}
			}
		}
	}
	// AI's Turn -- Black Player
	else
	{
		// Absolute max() value for an integer to store is necessary for the AI's Turn
		minmax = std::numeric_limits<int>::max();
		allMoves = ChessBoard.allMoves(black);

		for (GameObjectMoves::iterator it = allMoves.begin(); it != allMoves.end(); it++)
		{
			// These Coordinates represent the GameObject we are going to move
			coordinates = it->first;

			for (unsigned int i = 0; i < it->second.size(); i++)
			{
				std::unique_ptr<Board> copy = ChessBoard.clone();
				endCoordinates = it->second[i];
				copy->minmaxUpdate(coordinates, endCoordinates);

				// minmaxUpdate does not guarantee that there won't be a move that puts the AI's King in check, if so then we just disregard it by only accepting valid boards
				if (!copy->kingInCheck(black)) {
					moveBonus = bonus + bonusPoints(endCoordinates.first, endCoordinates.second, copy->piece(endCoordinates.first, endCoordinates.second));
					minmax = std::min(minmax, search(depth - 1, *copy, moveMap, moveBonus, nextTurn, alpha, beta));
					
					beta = std::min(beta, minmax);

					if (alpha >= beta)
						break; // Alpha cut-off
					
					if (depth == MAX_DEPTH)
						moveMap.insert({minmax, Move { coordinates, endCoordinates }});
				}
			}
		}

	}

	return minmax;
}

int Chess::ChessAI::evaluate(const Board & ChessBoard, int bonus)
{
	return (ChessBoard.points(black) + bonus) - ChessBoard.points(white);
}

int Chess::ChessAI::bonusPoints(int row, int column, char piece)
{
	return table.get(row, column, piece);
}

Chess::ChessAI::~ChessAI()
{

}
