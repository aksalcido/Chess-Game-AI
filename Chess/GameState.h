#include <vector>

class GameState
{
public:
	GameState();

	~GameState();

private:
	std::vector <std::vector<char>> board
	{
		{'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R'},
		{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' },
		{'.', '.', '.', '.', '.', '.', '.', '.'},
		{'.', '.', '.', '.', '.', '.', '.', '.'},
		{'.', '.', '.', '.', '.', '.', '.', '.'},
		{'.', '.', '.', '.', '.', '.', '.', '.'},
		{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
		{'r', 'h', 'b', 'k', 'q', 'b', 'h', 'r'}
	};


};
