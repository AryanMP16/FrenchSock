#include "Board.h"
#include <iostream>

Board::Board() { //O(1)
	for (int file = 0; file < 8; file++) {
		boardArr[1][file].piece = 'P';
		boardArr[6][file].piece = 'p';
		boardArr[0][file].piece = whitePieces[file];
		boardArr[7][file].piece = blackPieces[file];
		for (int rank = 0; rank < 8; rank++) {
			if(rank >= 2 && rank <= 5)
				boardArr[rank][file].piece = '.';
			boardArr[rank][file].file = files[file];
			boardArr[rank][file].rank = ranks[rank];
		}
		
	}
}

void Board::viewBoard() { //O(1)
	for (int file = 7; file >= 0; file--) {
		for (int rank = 0; rank < 8; rank++) {
			std::cout << boardArr[file][rank].piece << "  ";
		}
		std::cout << std::endl;
	}
}

Board::square* Board::operator[](std::string file_rank) { //O(1)
	if (file_rank.size() != 2) {
		std::cout << "Abort 1 called from Board::operator[]";
		abort();
	}
	else if (file_rank == "//") {
		std::cout << "Abort 2 called from Board::operator[]";
	}
	char file = file_rank.substr(0, 1)[0];
	int rank = std::stoi(file_rank.substr(1, 1));

	for (int boardFiles = 0; boardFiles < 8; boardFiles++) {
		for (int boardRanks = 0; boardRanks < 8; boardRanks++) {
			if (boardArr[boardRanks][boardFiles].file == file && boardArr[boardRanks][boardFiles].rank == rank)
				return &boardArr[boardRanks][boardFiles];

		}
	}
	std::cout << "Abort 3 called from Board::operator[]";
	abort();
}

void Board::editSquare(Board::square* toEdit, char pieceToChangeTo) { //O(1)
	for (int rank = 0; rank < 8; rank++) {
		for (int file = 0; file < 8; file++) {
			if (&boardArr[rank][file] == toEdit) {
				boardArr[rank][file].piece = pieceToChangeTo;
				return;
			}
		}
	}
	std::cout << "Abort 1 called from Board::editSquare";
	abort();
}

void Board::makeMove(std::string algebraicMove) { //O(1) --> even though substr runs on O(N), since our N is always 5, our time complexity is O(1)
	if (algebraicMove.size() != 5) {
		std::cout << "Abort 1 called from Board::makeMove";
		abort();
	}
	std::string originatingSquare = algebraicMove.substr(0, 2);
	std::string endingSquare = algebraicMove.substr(3, 2);

	if (originatingSquare == endingSquare) {
		return;
	}
	
	this->editSquare((*this)[endingSquare], (*this)[originatingSquare]->piece);
	this->editSquare((*this)[originatingSquare], '.');
}

std::vector<Board::square> Board::piecesLeft(std::string side) {
	std::vector<Board::square> toReturn;
	for (int rank = 0; rank < 8; rank++) {
		for (int file = 0; file < 8; file++) {
			if (side == "white") {
				if (isupper(boardArr[rank][file].piece) == true)
					toReturn.push_back(boardArr[rank][file]);
			}
			else {
				if (isupper(boardArr[rank][file].piece) == false && boardArr[rank][file].piece != '.')
					toReturn.push_back(boardArr[rank][file]);
			}
		}
	}
	return toReturn;
}

int Board::getPointValue(char piece) const { // O(1)
	int piecePoints[8] = { 5, 3, 3, 9, 1000, 3, 3, 5 };
	if (isupper(piece) == true) {
		for (int i = 0; i < 8; i++) {
			if (whitePieces[i] == piece) {
				return piecePoints[i];
			}
		}
	}
	else if (isupper(piece) == false && piece != '.') {
		for (int i = 0; i < 8; i++) {
			if (blackPieces[i] == piece) {
				return piecePoints[i];
			}
		}
	}
}

double Board::evaluatePosition() {
	double toReturn = 0;
	std::vector<Board::square> whitePiecesRemaining = piecesLeft("white");
	std::vector<Board::square> blackPiecesRemaining = piecesLeft("black");

	for (int i = 0; i < whitePiecesRemaining.size(); i++) {
		toReturn += getPointValue(whitePiecesRemaining[i].piece);
	}
	for (int i = 0; i < blackPiecesRemaining.size(); i++) {
		toReturn -= getPointValue(blackPiecesRemaining[i].piece);
	}
	return toReturn + 0.13; //stockfish estimates that white has a +0.13 advantage because they go first
}

Board::square Board::viewSquare(int rank, int file) const {
	return boardArr[rank][file];
}

double Board::adjustEvalByPiecePlacement(char piece, std::string file_rank) const {
	double whitePawnPlacement[8][8] = {
		{-1, -1, -1, -1, -1, -1, -1, -1}, //1st rank
		{0, 0, 0, 0, 0, 0, 0, 0}, //2nd rank
		{0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1}, //3rd rank
		{0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2}, //4th rank
		{0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3}, //5th rank
		{0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4}, //6th rank
		{0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5}, //7th rank
		{9, 9, 9, 9, 9, 9, 9, 9} //8th rank
	};

	double blackPawnPlacement[8][8] = {
		{9, 9, 9, 9, 9, 9, 9, 9}, //1st rank
		{0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5}, //2nd rank
		{0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4}, //3rd rank
		{0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3}, //4th rank
		{0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2}, //5th rank
		{0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1}, //6th rank
		{0, 0, 0, 0, 0, 0, 0, 0}, //7th rank
		{-1, -1, -1, -1, -1, -1, -1, -1} //8th rank
	};

	double bishopPlacement[8][8] = {
		{0.5, 0.4, 0.3, 0.2, 0.2, 0.3, 0.4, 0.5}, //1st rank
		{0.4, 0.5, 0.3, 0.2, 0.2, 0.3, 0.5, 0.4}, //2nd rank
		{0.3, 0.4, 0.5, 0.2, 0.2, 0.5, 0.4, 0.3}, //3rd rank
		{0.2, 0.3, 0.4, 0.5, 0.5, 0.4, 0.3, 0.2}, //4th rank
		{0.2, 0.3, 0.4, 0.5, 0.5, 0.4, 0.3, 0.2}, //5th rank
		{0.3, 0.4, 0.5, 0.2, 0.2, 0.5, 0.4, 0.3}, //6th rank
		{0.4, 0.5, 0.3, 0.2, 0.2, 0.3, 0.5, 0.4}, //7th rank
		{0.5, 0.4, 0.3, 0.2, 0.2, 0.3, 0.4, 0.5} //8th rank
	};

	double whiteRookPlacement[8][8] = {
		{0, 0, 0.1, 0.2, 0.2, 0.1, 0, 0}, //1st rank
		{0, 0, 0.1, 0.2, 0.2, 0.1, 0, 0}, //2nd rank
		{0, 0, 0.1, 0.2, 0.2, 0.1, 0, 0}, //3rd rank
		{0.1, 0.1, 0.2, 0.3, 0.3, 0.2, 0.1, 0.1}, //4th rank
		{0.1, 0.1, 0.2, 0.3, 0.3, 0.2, 0.1, 0.1}, //5th rank
		{0, 0, 0.1, 0.2, 0.2, 0.1, 0, 0}, //6th rank
		{0.3, 0.3, 0.4, 0.5, 0.5, 0.4, 0.3, 0.3}, //7th rank
		{0.1, 0.1, 0.2, 0.3, 0.3, 0.2, 0.1, 0.1} //8th rank
	};

	double blackRookPlacement[8][8] = {
		{0.1, 0.1, 0.2, 0.3, 0.3, 0.2, 0.1, 0.1}, //1st rank
		{0.3, 0.3, 0.4, 0.5, 0.5, 0.4, 0.3, 0.3}, //2nd rank
		{0, 0, 0.1, 0.2, 0.2, 0.1, 0, 0}, //3rd rank
		{0.1, 0.1, 0.2, 0.3, 0.3, 0.2, 0.1, 0.1}, //4th rank
		{0.1, 0.1, 0.2, 0.3, 0.3, 0.2, 0.1, 0.1}, //5th rank
		{0, 0, 0.1, 0.2, 0.2, 0.1, 0, 0}, //6th rank
		{0, 0, 0.1, 0.2, 0.2, 0.1, 0, 0}, //7th rank
		{0, 0, 0.1, 0.2, 0.2, 0.1, 0, 0} //8th rank
	};

	double queenPlacement[8][8] = {
		{0.3, 0.1, 0.2, 0.3, 0.3, 0.2, 0.1, 0.3}, //1st rank
		{0.3, 0.3, 0.4, 0.5, 0.5, 0.4, 0.3, 0.3}, //2nd rank
		{0, 0, 0.1, 0.3, 0.3, 0.1, 0, 0}, //3rd rank
		{0.1, 0.1, 0.2, 0.5, 0.5, 0.2, 0.1, 0.1}, //4th rank
		{0.1, 0.1, 0.2, 0.5, 0.5, 0.2, 0.1, 0.1}, //5th rank
		{0, 0, 0.1, 0.3, 0.3, 0.1, 0, 0}, //6th rank
		{0.3, 0.3, 0.4, 0.5, 0.5, 0.4, 0.3, 0.3}, //7th rank
		{0.3, 0.1, 0.2, 0.3, 0.3, 0.2, 0.1, 0.3} //8th rank
	};

	double knightPlacement[8][8] = {
		{-0.3, 0, 0, 0, 0, 0, 0, -0.3}, //1st rank
		{-0.1, 0, 0, 0, 0, 0, 0, -0.1}, //2nd rank
		{-0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, -0.1}, //3rd rank
		{-0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, -0.1}, //4th rank
		{-0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, -0.1}, //5th rank
		{-0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, -0.1}, //6th rank
		{-0.1, 0, 0, 0, 0, 0, 0, -0.1}, //7th rank
		{-0.3, 0, 0, 0, 0, 0, 0, -0.3} //8th rank
	};

	double kingPlacement[8][8] = {
		{0, 0, 0, 0, 0, 0, 0, 0}, //1st rank
		{0, 0, 0, 0, 0, 0, 0, 0}, //2nd rank
		{0, 0, 0, 0, 0, 0, 0, 0}, //3rd rank
		{0, 0, 0, 0, 0, 0, 0, 0}, //4th rank
		{0, 0, 0, 0, 0, 0, 0, 0}, //5th rank
		{0, 0, 0, 0, 0, 0, 0, 0}, //6th rank
		{0, 0, 0, 0, 0, 0, 0, 0}, //7th rank
		{0, 0, 0, 0, 0, 0, 0, 0} //8th rank
	};

	if (file_rank == "//") {}

	char file = file_rank.substr(0, 1)[0];
	int fileInt = 0;
	int rank = std::stoi(file_rank.substr(1, 1));
	int rankInt = rank - 1;

	for (int i = 0; i < 8; i++) {
		if (files[i] == file) {
			fileInt = i;
			break;
		}
	}

	if (piece == 'P')
		return whitePawnPlacement[rankInt][fileInt];
	else if (piece == 'p')
		return blackPawnPlacement[rankInt][fileInt];
	else if (piece == 'R')
		return whiteRookPlacement[rankInt][fileInt];
	else if (piece == 'r')
		return blackRookPlacement[rankInt][fileInt];
	else if (piece == 'n' || piece == 'N')
		return knightPlacement[rankInt][fileInt];
	else if (piece == 'b' || piece == 'B')
		return bishopPlacement[rankInt][fileInt];
	else if (piece == 'q' || piece == 'Q')
		return queenPlacement[rankInt][fileInt];
	else if (piece == 'k' || piece == 'K')
		return kingPlacement[rankInt][fileInt];
	else {
		std::cout << "Abort 1 called from Board::adjustEvalByPiecePlacement";
		abort();
	}
}