#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameObject.h"
#include <iostream>
#include <memory>

class GameState
{
public:
	// Default Constructor for the Chess GameState Class
	GameState();

	// Returns a Boolean in regards to if the move is a valid for the GameState, false otherwise.
	bool validateMove(int row, int col, int endRow, int endCol);

	// Displays the GameState in a user-friendly console interface.
	void display() const;

	// Returns a Boolean in regards to if the game is over or not; True if game is still continuing, false otherwise.
	bool continuing() const;

	// Destructor for the GameState, releases remainder GameObjects on the board that were dynamically allocated
	~GameState();

private:
	Chess::GameObject * board[dimension][dimension];
	int turn;
	bool GameOver;

private:
	// Initializes the Board to contain GameObject pieces similar to the char representation of the Board, This allows the board
	// to become fully accessible game objects that allow the game to progress, rather than simply using char types.
	void initialize(Chess::GameObject(*board[dimension][dimension]));

	// inBounds takes the user input and returns True if is it within boundaries of the board. False otherwise.
	bool inBounds(int row, int column);
};

#endif // GAMESTATE_H