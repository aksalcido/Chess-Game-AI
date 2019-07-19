#ifndef GAMESTATE_H
#define GAMESTATE_H
#pragma once
#include <iostream>
#include <memory>
#include "Board.h"
#include "ChessAI.h"

namespace Chess {

	class GameState
	{
	public:
		// Default Constructor for the Chess GameState Class
		GameState();

		// Progresses the Game of Chess updating the current Gamestate each time
		void progress(int row, int col, int endRow, int endCol);

		void progressAI();

		// Completes the movement made on the board using the coordinates made from the user
		void movement(int row, int col, int endRow, int endCol);

		void initializeAI(int difficulty);

		// Switches the turn to the next player
		void nextTurn();

		// Returns a Boolean true if it is the Player's turn, false otherwise.
		bool playersTurn();

		// Returns a Boolean in regards to if the move is a valid for the GameState, false otherwise.
		bool validateMove(int row, int col, int endRow, int endCol);

		// Displays the GameState in a user-friendly console interface.
		void display() const;

		// Displays the Move made by the User
		void displayMove(int startRow, int startColumn, int endRow, int endColumn) const;

		// Displays to the user that their king is in check
		void displayCheck() const;

		// Displays the winner of the game to the console
		void displayWinner() const;
	
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
		ChessAI ChessBot;
		int turn;
		bool GameOver;

		// Checks if promotion has occured during the last turn, if so the necessary promotion rules are handled in this function
		void promotionCheck(int row, int col);

		// Checks if a move was castling, ensures the GameObject's boolean hasNotMoved is changed, and updates the coordinates of the GameObject
		void checksAndUpdates(int row, int col);

		// Displays the piece options to the User when Pawn Promotion is reached and accepts input on which GameObject they want
		int displayPieceOptions();

		// Returns a Boolean whether the coordinates (row, col) and (endRow, endCol) are on the board
		bool playersMoveOnBoard(int row, int col, int endRow, int endCol) const;

		// Returns a Boolean whether the Start Position is a GameObject and the start (row, col) must be the Player's GameObject
		bool isPlayersPiece(int row, int col) const;

	};
};

#endif // GAMESTATE_H