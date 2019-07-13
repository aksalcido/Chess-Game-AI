#ifndef GAMESTATE_H
#define GAMESTATE_H
#pragma once
#include <iostream>
#include <memory>
#include "Board.h"

namespace Chess {
	class GameState
	{
	public:
		// Default Constructor for the Chess GameState Class
		GameState();

		// Progresses the Game of Chess updating the current Gamestate each time
		void progress(int row, int col, int endRow, int endCol);

		// Completes the movement made on the board using the coordinates made from the user
		void movement(int row, int col, int endRow, int endCol);

		// Switches the turn to the next player
		void nextTurn();

		// Returns a Boolean in regards to if the move is a valid for the GameState, false otherwise.
		bool validateMove(int row, int col, int endRow, int endCol);

		// Displays the GameState in a user-friendly console interface.
		void display() const;

		// Displays the Move made by the User
		void displayMove(int startRow, int startColumn, int endRow, int endColumn) const;

		// Prompts the User a message argument to the console
		void prompt(const char * message);

		// Receives input from the User for the coordinates on the Board
		void input(int & row, int & col, int & endRow, int & endCol);

		// Returns a Boolean in regards to if the game is over or not; True if game is still continuing, false otherwise.
		bool continuing() const;

		// Destructor for the GameState
		~GameState();

	private:
		Board ChessBoard;
		int turn;
		bool GameOver;

		// Returns a Boolean whether the coordinates (row, col) and (endRow, endCol) are on the board
		bool playersMoveOnBoard(int row, int col, int endRow, int endCol) const;

		// Returns a Boolean whether the Start Position is a GameObject and the start (row, col) must be the Player's piece
		bool isPlayersPiece(int row, int col) const;

	};
};

#endif // GAMESTATE_H