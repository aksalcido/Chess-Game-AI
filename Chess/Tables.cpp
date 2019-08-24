#include "Tables.h"


Chess::Tables::Tables()
{
	initializeKingTable();
	initializeQueenTable();
	initializeRookTable();
	initializeBishopTable();
	initializeKnightTable();
	initializePawnTable();
}

int Chess::Tables::get(int row, int column, char piece)
{
	switch (piece) {
		case BLACK_PAWN:
			return BlackPawnPositions[row][column];

		case BLACK_BISHOP:
			return BlackBishopPositions[row][column];

		case BLACK_KNIGHT:
			return BlackKnightPositions[row][column];

		case BLACK_ROOK:
			return BlackRookPositions[row][column];

		case BLACK_QUEEN:
			return BlackQueenPositions[row][column];

		case BLACK_KING:
			return BlackKingPositions[row][column];

		case WHITE_PAWN:
			return WhitePawnPositions[row][column];

		case WHITE_BISHOP:
			return WhiteBishopPositions[row][column];

		case WHITE_KNIGHT:
			return WhiteKnightPositions[row][column];

		case WHITE_ROOK:
			return WhiteRookPositions[row][column];

		case WHITE_QUEEN:
			return WhiteQueenPositions[row][column];

		case WHITE_KING:
			return WhiteKingPositions[row][column];
	}
}

void Chess::Tables::setup(int pos[dimension][dimension], int whitePos[dimension][dimension], int blackPos[dimension][dimension])
{
	for (unsigned int i = 0; i < dimension; i++)
	{
		for (unsigned int j = 0; j < dimension; j++)
		{
			whitePos[i][j] = pos[i][j];
			blackPos[dimension - i][j] = pos[i][j];
		}
	}
}

void Chess::Tables::initializeKingTable()
{
	int pos[dimension][dimension] = 
	{
		{ -3, -4, -4, -5, -5, -4, -4, -3},
		{ -3, -4, -4, -5, -5, -4, -4, -3},
		{ -3, -4, -4, -5, -5, -4, -4, -3},
		{ -3, -4, -4, -5, -5, -4, -4, -3},
		{ -2, -3, -3, -4, -4, -3, -3, -2},
		{ 1, 2, 0, 0, 0, 0, 2, 1},
		{ 2, 3, 1, 0, 0, 1, 3, 2},
	};

	setup(pos, WhiteKingPositions, BlackKingPositions);
}

void Chess::Tables::initializeQueenTable()
{
	int pos[dimension][dimension] = 
	{
		{-3, -2, -2, -1, -1, -2, -2, -3 },
		{-2, 0, 0, 0, 0, 0, 0, -2},
		{-2, 0, 1, 1, 1, 1, 0, -2},
		{-1, 0, 1, 1, 1, 1, 0, -1},
		{0, 0, 1, 1, 1, 1, 0, -1},
		{-2, 1, 1, 1, 1, 1, 0, -2},
		{ -2, 0, -1, 0, 0, 0, 0, -2 },
		{ -3, -2, -2, -1, -1, -2, -2, -3 },
	};

	setup(pos, WhiteQueenPositions, BlackQueenPositions);
}

void Chess::Tables::initializeRookTable()
{
	int pos[dimension][dimension] = 
	{
		{0, -2, 0, 0, 0, 0, -2, 0},
		{1, 2, 2, 2, 2, 2, 2, 1},
		{-1, 0, 0, 0, 0, 0, 0, -1},
		{ -1, 0, 0, 0, 0, 0, 0, -1 },
		{ -1, 0, 0, 0, 0, 0, 0, -1 },
		{ -1, 0, 0, 0, 0, 0, 0, -1 },
		{ -1, 0, 0, 0, 0, 0, 0, -1 }, 
		{0, -2, 0, 1, 1, 0, -2, 0}
	};

	setup(pos, WhiteRookPositions, BlackRookPositions);
}

void Chess::Tables::initializeBishopTable()
{
	int pos[dimension][dimension] =
	{
		{-2, -1, -1, -1, -1, -1, -1, -2},
		{-1, 0, 0, 0, 0, 0, 0, -1},
		{-1, 0, 1, 2, 2, 1, 0, -1},
		{-1, 1, 1, 2, 2, 1, 1, -1},
		{-1, 0, 1, 2, 2, 2, 0, -1},
		{-1, 1, 1, 1, 1, 1, 1, -1},
		{-1, 1, 0, 0, 0, 0, 1, -1},
		{-2, -1, -1, -1, -1, -1, -1, -2}
	};
	
	setup(pos, WhiteRookPositions, BlackRookPositions);
}

void Chess::Tables::initializeKnightTable()
{
	int pos[dimension][dimension] =
	{
		{ -5, -4, -3, -3, -3, -3, -4, -5 },
		{ -4, -2, 0, 0, 0, 0, -2, -4 },
		{ -5, 0, 1, 2, 2, 1, 0, -5 },
		{ -3, 1, 2, 3, 3, 2, 1, -3 },
		{ -3, 0, 2, 3, 3, 2, 0, -3 },
		{ -3, 1, 1, 2, 2, 1, 1, -3 },
		{ -4, -2, 0, 1, 1, 0, -2, -4 },
		{ -5, -4, -3, -3, -3, -3, -4, -5 }
	};

	setup(pos, WhiteKnightPositions, BlackKnightPositions);
}

void Chess::Tables::initializePawnTable()
{
	int pos[dimension][dimension] =
	{
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 5, 5, 5, 5, 5, 5, 5, 5 },
		{ 1, 1, 2, 8, 8, 2, 1, 1 },
		{ 1, 1, 8, 10, 10, 8, 1, 1 },
		{ 0, 0, 0, 10, 10, 0, 0, 0 },
		{ 1, -1, -1, 4, 4, -1, -1, 1 },
		{ 1, 1, 1, -2, -2, 1, 1, 1 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 }
	};

	setup(pos, WhitePawnPositions, BlackPawnPositions);
}

Chess::Tables::~Tables()
{

}
