#include "GameObject.h"
#include <iostream>
#include <vector>
#include <memory>

#define white 0
#define black 1
#define empty 2
#define dimension 8

class GameState
{
public:
	GameState() : turn(white), GameOver(false)
	{
		initialize();
	}

	void initialize()
	{
		// Initializes a Local representation of the Chess board to place Chess Objects onto the board
		std::vector < std::vector<char>> representation
		{
			{ 'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R' },
			{ 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' },
			{ '.', '.', '.', '.', '.', '.', '.', '.' },
			{ '.', '.', '.', '.', '.', '.', '.', '.' },
			{ '.', '.', '.', '.', '.', '.', '.', '.' },
			{ '.', '.', '.', '.', '.', '.', '.', '.' },
			{ 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p' },
			{ 'r', 'h', 'b', 'k', 'q', 'b', 'h', 'r' },
		};

		for (unsigned int i = 0; i < dimension; i++)
		{

			for (unsigned int j = 0; j < dimension; j++)
			{
				char square = representation[i][j];
				int color = (i < 2 ? black : white);

				switch (square) {

				case 'R':
					board[i][j] = Chess::Rook(j, i, color, square);
					break;

				case 'H':
					board[i][j] = Chess::Knight(j, i, color, square);
					break;

				case 'B':
					board[i][j] = Chess::Bishop(j, i, color, square);
					break;

				case 'Q':
					board[i][j] = Chess::Queen(j, i, color, square);
					break;

				case 'K':
					board[i][j] = Chess::King(j, i, color, square);
					break;

				case 'P':
					board[i][j] = Chess::Pawn(j, i, color, square);
					break;

				default:
					board[i][j] = Chess::Square(j, i, empty, square);
					break;
				}
			}
		}
	}

	void display() 
	{
		std::cout << "   0 1 2 3 4 5 6 7" << std::endl;
		std::cout << " -------------------" << std::endl;

		for (unsigned int i = 0; i < dimension; i++)
		{
			std::cout << i << "| ";

			for (unsigned int j = 0; j < dimension; j++) {
				std::cout << board[i][j].displayPiece() << " ";
			}

			std::cout << "|" << std::endl;
		}

		std::cout << " -------------------" << std::endl;

		if (!GameOver) 
			std::cout << "It is " << (turn == white ? "white's " : "black's ") << "turn to move!" << std::endl;
	}

	bool continuing()
	{
		return ! GameOver;
	}

	~GameState()
	{

	}

private:
	Chess::GameObject board[dimension][dimension];
	int turn;
	bool GameOver;
};
