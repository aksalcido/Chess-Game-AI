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

	return Move{ coordinates, move };
}

Move Chess::ChessAI::normalMove(Board * ChessBoard)
{
	std::map<int, Move> moveMap;
	int minmax = search(MAX_DEPTH, *ChessBoard, moveMap, 0);

	return moveMap[minmax];
}

int Chess::ChessAI::search(int depth, const Board & ChessBoard, std::map<int, Move> & moveMap, int bonus)
{
	if (depth == 0)
		return evaluate(ChessBoard, bonus);

	int minmax, moveScore = 0, moveBonus = 0;
	GameObjectMoves allMoves;
	std::pair<int, int> coordinates, endCoordinates;

	// Player's Turn -- White Player
	if (depth % 2 == 0)
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
				moveBonus = bonus + bonusPoints(endCoordinates.first, endCoordinates.second, copy->piece(coordinates.first, coordinates.second));
				copy->minmaxUpdate(coordinates, endCoordinates);

				// minmaxUpdate does not guarantee that there won't be a move that puts the Player's King in check, if so then we just disregard it by only accepting valid boards
				if (!copy->kingInCheck(white))
					minmax = std::max(minmax, search(depth - 1, *copy, moveMap, moveBonus));
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
				moveBonus = bonus + bonusPoints(endCoordinates.first, endCoordinates.second, copy->piece(coordinates.first, coordinates.second));
				copy->minmaxUpdate(coordinates, endCoordinates);

				// minmaxUpdate does not guarantee that there won't be a move that puts the AI's King in check, if so then we just disregard it by only accepting valid boards
				if (!copy->kingInCheck(black)) {
					minmax = std::min(minmax, search(depth - 1, *copy, moveMap, moveBonus));

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
	return ChessBoard.points(black) - ChessBoard.points(white) + bonus;
}

int Chess::ChessAI::bonusPoints(int row, int column, char piece)
{
	return table.get(row, column, piece);
}

Chess::ChessAI::~ChessAI()
{

}
