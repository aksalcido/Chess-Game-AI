#include "Board.h"
#include <iostream>

Chess::Board::Board() {
	initialize(board);
}

Chess::Board::Board(const Board & b) {
	copy(b);
}

void Chess::Board::movementToEmptySquare(int row, int col, int endRow, int endCol) {
	std::swap(board[row][col], board[endRow][endCol]);
}

void Chess::Board::movementToEnemy(int row, int col, int endRow, int endCol) {
	updatePieces(board[endRow][endCol]);
	delete board[endRow][endCol];
	board[endRow][endCol] = nullptr;

	std::swap(board[row][col], board[endRow][endCol]);
}

void Chess::Board::updateCoordinates(int newRow, int newCol) {
	board[newRow][newCol]->changeCoordinates(newRow, newCol);
}

void Chess::Board::playerStatus() {
	((King*)blackKing)->checkedStatus(this);
	((King*)whiteKing)->checkedStatus(this);
}

void Chess::Board::minmaxUpdate(std::pair<int, int> start, std::pair<int, int> end) {
	if (emptySpace(end.first, end.second))
		movementToEmptySquare(start.first, start.second, end.first, end.second);
	else
		movementToEnemy(start.first, start.second, end.first, end.second);

	updateCoordinates(end.first, end.second);
	playerStatus();
}

void Chess::Board::firstMoveCheck(int row, int col) {
	board[row][col]->firstMoveOccured();
}

void Chess::Board::castlingCheck(int row, int col) {
	if (pieceHasNotMoved(row, col) && (piece(row, col) == BLACK_KING || piece(row,col) == WHITE_KING) && (col == dimension - 2)) {
		std::swap(board[row][col - 1], board[row][col + 1]);
		board[row][col - 1] -> changeCoordinates(row, col - 1); // change coordinates of Rook after castling
	}
}


void Chess::Board::gameFinishedCheck(int turn, bool currentlyChecked) {
	std::vector<GameObject*> pieces = (turn == black ? blackPieces : whitePieces);
	Moves moves;

	bool outOfMoves = true;

	// Best Case and average case will iterate through the first one and immediately break
	// Worst Case will iterate through all of the Pieces and the last one will have moves in the case that it is not game over
	for (std::vector<GameObject*>::iterator it = pieces.begin(); it != pieces.end(); it++) {
		moves = (*it)->acquireMoves(this);

		// If the player is currentlyChecked and if the Player has moves available, the game is not over so we can break out of this check
		if (currentlyChecked) {
			if (moves.size() != 0) {
				outOfMoves = false;
				break;
			}
		}

		// Unfortunately when checking for a Stalemate, we have to test each specific move independently
		else {
			std::pair<int, int> pieceCoordinates = (*it)->getCoordinates();

			for (int i = 0; i < moves.size(); i++) {

				if (safeMove(pieceCoordinates.first, pieceCoordinates.second, moves[i].first, moves[i].second)) {
					outOfMoves = false;
					break;
				}
			}
		}
	}

	if (outOfMoves)
		throw GameOverException();
}

void Chess::Board::promote(int row, int col, int promoted) {
	int color = board[row][col]->pieceColor();
	char rep;

	// Handles removing the Pawn from our GameObjects vector and deallocating the memory
	updatePieces(board[row][col]);
	delete board[row][col];
	
	// Handles the different cases of what Piece the user wants
	switch (promoted) {
		case QUEEN_PROMOTION:
			rep = (color == white ? WHITE_QUEEN : BLACK_QUEEN);
			board[row][col] = new Queen(row, col, color, rep);
			break;

		case ROOK_PROMOTION:
			rep = (color == white ? WHITE_ROOK : BLACK_ROOK);
			board[row][col] = new Rook(row, col, color, rep);
			break;

		case BISHOP_PROMOTION:
			rep = (color == white ? WHITE_BISHOP : BLACK_BISHOP);
			board[row][col] = new Bishop(row, col, color, rep);
			break;

		case KNIGHT_PROMOTION:
			rep = (color == white ? WHITE_KNIGHT : BLACK_KNIGHT);
			board[row][col] = new Knight(row, col, color, rep);
			break;
	}

	// Add the promoted piece to our GameObjects vector
	if (color == white)
		whitePieces.push_back(board[row][col]);
	else
		blackPieces.push_back(board[row][col]);
}

bool Chess::Board::promotion(int row, int col) {
	int maxRow = (pieceColor(row, col) == white ? 0 : 7);

	// Promotion Rules: If a Pawn reaches the end row of the board for the respective player, then they are granted a new piece of their choosing
	return ((piece(row, col) == WHITE_PAWN || piece(row, col) == BLACK_PAWN) && row == maxRow);
}

bool Chess::Board::pieceHasNotMoved(int row, int col) const {
	return board[row][col]->initialPosition();
}

bool Chess::Board::validMove(int row, int col, int endRow, int endCol) {
	return board[row][col] -> validMove(endRow, endCol, this);
}


bool Chess::Board::safeMove(int row, int col, int endRow, int endCol) const {
	std::unique_ptr<Board> copy = clone();

	if (copy->emptySpace(endRow, endCol))
		copy->movementToEmptySquare(row, col, endRow, endCol);
	else
		copy->movementToEnemy(row, col, endRow, endCol);

	copy->updateCoordinates(endRow, endCol);
	copy->playerStatus();

	return !copy->kingInCheck(copy->pieceColor(endRow, endCol));
}


bool Chess::Board::emptySpace(int row, int col) const {
	return ( inBounds(row, col) ? board[row][col] == nullptr : false );
}

bool Chess::Board::enemySpace(int row, int col, int dx, int dy) const {
	if (inBounds(dx, dy))
		return !emptySpace(dx, dy) && board[row][col]->oppositePlayer(pieceColor(dx, dy));

	return false;
}

bool Chess::Board::enemyCheckingKing(int enemyRow, int enemyCol, int kingRow, int kingCol) const {
	return board[enemyRow][enemyCol]->canAttackEnemy(kingRow, kingCol, this);
}

bool Chess::Board::inBounds(int row, int col) const {
	return (0 <= row && row < dimension) && (0 <= col && col < dimension);
}


bool Chess::Board::kingInCheck(int color) const {
	if (color == white)
		return ((King*)whiteKing)->inCheck();
	else
		return ((King*)blackKing)->inCheck();
}


char Chess::Board::piece(int row, int col) const {
	return board[row][col]->displayPiece();
}

int Chess::Board::pieceColor(int row, int col) const {
	return board[row][col]->pieceColor();
}

int Chess::Board::points(int color) const {
	int total = 0;
	char rep;

	std::vector<GameObject*> container = (color == white ? whitePieces : blackPieces);
	
	for (int i = 0; i < container.size(); i++) {
		rep = container[i]->displayPiece();
		total += pieceValues.at(rep);
	}

	return total;
}

GameObjectMoves Chess::Board::allMoves(int color) const {
	// Container will be the dependent on the argument 'color' so that we are iterating through the game pieces of the correct player
	std::vector<GameObject*> container = (color == white ? whitePieces : blackPieces);

	// Initialize a map that will be the returned value of the Coordinates and Moves
	GameObjectMoves moveMap;

	// Initialize the key, value pairs for readability
	std::pair<int, int> coordinates;
	Moves pieceMoves;

	for (int i = 0; i < container.size(); i++) {
		coordinates = container[i]->getCoordinates();
		pieceMoves = container[i]->acquireMoves(this);

		moveMap.insert({ coordinates, pieceMoves });
	}

	return moveMap;
}

void Chess::Board::updatePieces(GameObject * pieceBeingRemoved) {
	std::vector<GameObject*> * container = &(pieceBeingRemoved->pieceColor() == white ? whitePieces : blackPieces);

	for (int i = 0; i < container->size(); i++) {
		if ((*container)[i] == pieceBeingRemoved) {
			container->erase((*container).begin() + i);
			break;
		}
	}
}

std::vector<Moves> Chess::Board::enemyPaths(int color) const {
	if (color == white)
		return ((King*)whiteKing)->enemies();
	else
		return ((King*)blackKing)->enemies();
}

std::unique_ptr<Chess::Board> Chess::Board::clone() const {
	std::unique_ptr<Board> board_ptr = std::make_unique<Board>(*this);

	return board_ptr;
}

void Chess::Board::copy(const Board & otherBoard) {
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			char statement = otherBoard.board[i][j] != nullptr ? otherBoard.board[i][j]->displayPiece() : 'D';

			switch (statement) {
				case BLACK_ROOK:
					board[i][j] = new Rook(i, j, black, BLACK_ROOK);
					break;

				case WHITE_ROOK:
					board[i][j] = new Rook(i, j, white, WHITE_ROOK);
					break;

				case BLACK_KNIGHT:
					board[i][j] = new Knight(i, j, black, BLACK_KNIGHT);
					break;

				case WHITE_KNIGHT:
					board[i][j] = new Knight(i, j, white, WHITE_KNIGHT);
					break;

				case BLACK_BISHOP:
					board[i][j] = new Bishop(i, j, black, BLACK_BISHOP);
					break;

				case WHITE_BISHOP:
					board[i][j] = new Bishop(i, j, white, WHITE_BISHOP);
					break;

				case BLACK_QUEEN:
					board[i][j] = new Queen(i, j, black, BLACK_QUEEN);
					break;

				case WHITE_QUEEN:
					board[i][j] = new Queen(i, j, white, WHITE_QUEEN);
					break;

				case BLACK_KING:
					board[i][j] = new King(i, j, black, BLACK_KING);
					blackKing = board[i][j];
					break;

				case WHITE_KING:
					board[i][j] = new King(i, j, white, WHITE_KING);
					whiteKing = board[i][j];
					break;

				case BLACK_PAWN:
					board[i][j] = new Pawn(i, j, black, BLACK_PAWN);
					break;

				case WHITE_PAWN:
					board[i][j] = new Pawn(i, j, white, WHITE_PAWN);
					break;

				default:
					board[i][j] = nullptr;
					break;
			}

			if (board[i][j] != nullptr) {
				board[i][j]->copy(otherBoard.board[i][j]);

				if (board[i][j]->pieceColor() == black)
					blackPieces.push_back(board[i][j]);

				else if (board[i][j]->pieceColor() == white)
					whitePieces.push_back(board[i][j]);
			}
		}
	}

	pieceValues = otherBoard.pieceValues;
}



void Chess::Board::initialize(GameObject(*board[dimension][dimension])) {
	// Initializes a Local representation of the Chess board to place Chess Objects onto the board
	char representation[dimension][dimension] {
		{ 'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R' },
		{ 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' },
		{ '.', '.', '.', '.', '.', '.', '.', '.' },
		{ '.', '.', '.', '.', '.', '.', '.', '.' },
		{ '.', '.', '.', '.', '.', '.', '.', '.' },
		{ '.', '.', '.', '.', '.', '.', '.', '.' },
		{ 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p' },
		{ 'r', 'h', 'b', 'q', 'k', 'b', 'h', 'r' },
	};

	for (unsigned int i = 0; i < dimension; i++) {
		for (unsigned int j = 0; j < dimension; j++) {
			switch (representation[i][j]) {
				case BLACK_ROOK:
					board[i][j] = new Rook(i, j, black, BLACK_ROOK);
					pieceValues.insert({ BLACK_ROOK , 500 });
					break;

				case WHITE_ROOK:
					board[i][j] = new Rook(i, j, white, WHITE_ROOK);
					pieceValues.insert({ WHITE_ROOK , 500 });
					break;

				case BLACK_KNIGHT:
					board[i][j] = new Knight(i, j, black, BLACK_KNIGHT);
					pieceValues.insert({ BLACK_KNIGHT , 250 });
					break;

				case WHITE_KNIGHT:
					board[i][j] = new Knight(i, j, white, WHITE_KNIGHT);
					pieceValues.insert({ WHITE_KNIGHT , 250 });
					break;

				case BLACK_BISHOP:
					board[i][j] = new Bishop(i, j, black, BLACK_BISHOP);
					pieceValues.insert({ BLACK_BISHOP , 250 });
					break;

				case WHITE_BISHOP:
					board[i][j] = new Bishop(i, j, white, WHITE_BISHOP);
					pieceValues.insert({ WHITE_BISHOP , 250 });
					break;

				case BLACK_QUEEN:
					board[i][j] = new Queen(i, j, black, BLACK_QUEEN);
					pieceValues.insert({ BLACK_QUEEN , 1000 });
					break;

				case WHITE_QUEEN:
					board[i][j] = new Queen(i, j, white, WHITE_QUEEN);
					pieceValues.insert({ WHITE_QUEEN , 1000 });
					break;

				case BLACK_KING:
					board[i][j] = new King(i, j, black, BLACK_KING);
					pieceValues.insert({ BLACK_KING , 10000 });
					blackKing = board[i][j];
					break;

				case WHITE_KING:
					board[i][j] = new King(i, j, white, WHITE_KING);
					pieceValues.insert({ WHITE_KING , 10000 });
					whiteKing = board[i][j];
					break;

				case BLACK_PAWN:
					board[i][j] = new Pawn(i, j, black, BLACK_PAWN);
					pieceValues.insert({ BLACK_PAWN , 50 });
					break;

				case WHITE_PAWN:
					board[i][j] = new Pawn(i, j, white, WHITE_PAWN);
					pieceValues.insert({ WHITE_PAWN , 50 });
					break;

				default:
					board[i][j] = nullptr;
					break;
			}

			if (board[i][j] != nullptr && board[i][j]->pieceColor() == black)
				blackPieces.push_back(board[i][j]);

			else if (board[i][j] != nullptr && board[i][j]->pieceColor() == white)
				whitePieces.push_back(board[i][j]);
		}
	}
}


Chess::Board::~Board() {
	for (unsigned int i = 0; i < dimension; i++) {
		for (unsigned int j = 0; j < dimension; j++) {
			if (board[i][j] != nullptr)
				delete board[i][j];
		}
	}
}