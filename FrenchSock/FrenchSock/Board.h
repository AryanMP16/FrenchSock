#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>

class Board {
public:
	struct square {
		char file;
		int rank;
		char piece;
	};
	Board();
	void viewBoard();
	square* operator[](std::string file_rank); //used in instances like "board1[f3]"
	void makeMove(std::string algebraicMove); //takes inputs in the format of "h3:h4"
	void editSquare(square* toEdit, char pieceToChangeTo);
	std::vector<std::string> legalMoves(std::string squareOfInterestString);
	std::vector<Board::square> piecesLeft(std::string side);
	double evaluatePosition();
	int getPointValue(char piece) const;
	square viewSquare(int rank, int file) const;
private:
	square boardArr[8][8]; //first index is rank, second is file
	char blackPieces[8] = { 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r' };
	char whitePieces[8] = { 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R' };
	int ranks[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	char files[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
};

#endif