#include "Board.h"
#include <iostream>

//NOTE: no special rules like 2-square pawn moves, En Passant, and castling have been coded in yet

std::vector<std::string> Board::legalMoves(std::string squareOfInterestString) {
	square squareOfInterest = *((*this)[squareOfInterestString]);
	//creating vector that will be returned
	std::vector<std::string> toReturn;
	//extracting information from squareOfInterest
	char piece = squareOfInterest.piece;
	int fileIndex;
	for (fileIndex = 0; fileIndex < 8; fileIndex++) {
		if (squareOfInterest.file == files[fileIndex])
			break;
	}
	int rankIndex = squareOfInterest.rank - 1;
	std::string pieceColor;
	isupper(piece) == true ? pieceColor = "white" : pieceColor = "black";

	/*
	General Pseudocode:

	if piece is <piece>:
		if pieceColor is white:
			<determine legal moves for that white piece>
		else:
			<determine legal moves for that black piece>
	*/

	//PAWN
	if (piece == 'p' || piece == 'P') {
		if (pieceColor == "white") {
			for (int i = -1; i < 2; i++) {
				if (i == 0 && (rankIndex - 1) >= 0 && (rankIndex + 1) <= 7 && (fileIndex + i) >= 0 && (fileIndex + i) <= 7 && boardArr[rankIndex + 1][fileIndex + i].piece == '.') {
					toReturn.push_back(boardArr[rankIndex + 1][fileIndex + i].file + std::to_string(boardArr[rankIndex + 1][fileIndex + i].rank));
					if (boardArr[rankIndex + 2][fileIndex + i].piece == '.' && rankIndex == 1) {
						toReturn.push_back(boardArr[rankIndex + 2][fileIndex + i].file + std::to_string(boardArr[rankIndex + 2][fileIndex + i].rank));
					}
				}
				else if ((rankIndex - 1) >= 0 && (rankIndex + 1) <= 7 && (fileIndex + i) >= 0 && (fileIndex + i) <= 7 && i != 0 && (isupper(boardArr[rankIndex + 1][fileIndex + i].piece) == false) && boardArr[rankIndex + 1][fileIndex + i].piece != '.')
					toReturn.push_back(boardArr[rankIndex + 1][fileIndex + i].file + std::to_string(boardArr[rankIndex + 1][fileIndex + i].rank));
			}
		}
		else {
			for (int i = -1; i < 2; i++) {
				if (i == 0 && (rankIndex - 1) >= 0 && (rankIndex + 1) <= 7 && (fileIndex + i) >= 0 && (fileIndex + i) <= 7 && boardArr[rankIndex - 1][fileIndex + i].piece == '.') {
					toReturn.push_back(boardArr[rankIndex - 1][fileIndex + i].file + std::to_string(boardArr[rankIndex - 1][fileIndex + i].rank));
					if (boardArr[rankIndex - 2][fileIndex + i].piece == '.' && rankIndex == 6) {
						toReturn.push_back(boardArr[rankIndex - 2][fileIndex + i].file + std::to_string(boardArr[rankIndex - 2][fileIndex + i].rank));
					}
				}
				else if ((rankIndex - 1) >= 0 && (rankIndex + 1) <= 7 && (fileIndex + i) >= 0 && (fileIndex + i) <= 7 && i != 0 && (isupper(boardArr[rankIndex - 1][fileIndex + i].piece) == true) && boardArr[rankIndex - 1][fileIndex + i].piece != '.')
					toReturn.push_back(boardArr[rankIndex - 1][fileIndex + i].file + std::to_string(boardArr[rankIndex - 1][fileIndex + i].rank));
			}
		}
	}

	//KNIGHT
	else if (piece == 'n' || piece == 'N') {
		int fileIndArrN[8] = { fileIndex + 1, fileIndex + 2, fileIndex + 2, fileIndex + 1, fileIndex - 1, fileIndex - 2, fileIndex - 2, fileIndex - 1 };
		int rankIndArrN[8] = { rankIndex - 2, rankIndex - 1, rankIndex + 1, rankIndex + 2, rankIndex + 2, rankIndex + 1, rankIndex - 1, rankIndex - 2 };
		if (pieceColor == "white") {
			for (int i = 0; i < 8; i++) {
				if (fileIndArrN[i] >= 0 && fileIndArrN[i] <= 7 && rankIndArrN[i] >= 0 && rankIndArrN[i] <= 7 && (isupper(boardArr[rankIndArrN[i]][fileIndArrN[i]].piece) == false)) {
					toReturn.push_back(boardArr[rankIndArrN[i]][fileIndArrN[i]].file + std::to_string(boardArr[rankIndArrN[i]][fileIndArrN[i]].rank));
				}
			}
		}
		else {
			for (int i = 0; i < 8; i++) {
				if (fileIndArrN[i] >= 0 && fileIndArrN[i] <= 7 && rankIndArrN[i] >= 0 && rankIndArrN[i] <= 7 && (isupper(boardArr[rankIndArrN[i]][fileIndArrN[i]].piece) == true || boardArr[rankIndArrN[i]][fileIndArrN[i]].piece == '.'))
					toReturn.push_back(boardArr[rankIndArrN[i]][fileIndArrN[i]].file + std::to_string(boardArr[rankIndArrN[i]][fileIndArrN[i]].rank));
			}
		}
	}

	//ROOK
	else if (piece == 'r' || piece == 'R') {
		for (int rankIncrementer = 1; rankIncrementer <= 8; rankIncrementer++) {
			if (pieceColor == "white") {
				if (rankIndex + rankIncrementer >= 0 && rankIndex + rankIncrementer <= 7 && boardArr[rankIndex + rankIncrementer][fileIndex].piece == '.') {
					toReturn.push_back(boardArr[rankIndex + rankIncrementer][fileIndex].file + std::to_string(boardArr[rankIndex + rankIncrementer][fileIndex].rank));
				}
				else if (rankIndex + rankIncrementer >= 0 && rankIndex + rankIncrementer <= 7 && (isupper(boardArr[rankIndex + rankIncrementer][fileIndex].piece) == false) && boardArr[rankIndex + rankIncrementer][fileIndex].piece != '.') {
					toReturn.push_back(boardArr[rankIndex + rankIncrementer][fileIndex].file + std::to_string(boardArr[rankIndex + rankIncrementer][fileIndex].rank));
					break;
				}
				else if (rankIndex + rankIncrementer >= 0 && rankIndex + rankIncrementer <= 7 && (isupper(boardArr[rankIndex + rankIncrementer][fileIndex].piece) == true)) {
					break;
				}
			}
			else {
				if (rankIndex + rankIncrementer >= 0 && rankIndex + rankIncrementer <= 7 && boardArr[rankIndex + rankIncrementer][fileIndex].piece == '.') {
					toReturn.push_back(boardArr[rankIndex + rankIncrementer][fileIndex].file + std::to_string(boardArr[rankIndex + rankIncrementer][fileIndex].rank));
				}
				else if (rankIndex + rankIncrementer >= 0 && rankIndex + rankIncrementer <= 7 && (isupper(boardArr[rankIndex + rankIncrementer][fileIndex].piece) == true)) {
					toReturn.push_back(boardArr[rankIndex + rankIncrementer][fileIndex].file + std::to_string(boardArr[rankIndex + rankIncrementer][fileIndex].rank));
					break;
				}
				else if (rankIndex + rankIncrementer >= 0 && rankIndex + rankIncrementer <= 7 && (isupper(boardArr[rankIndex + rankIncrementer][fileIndex].piece) == false) && boardArr[rankIndex + rankIncrementer][fileIndex].piece != '.') {
					break;
				}
			}
		}

		for (int rankIncrementer = -1; rankIncrementer >= -8; rankIncrementer--) {
			if (pieceColor == "white") {
				if (rankIndex + rankIncrementer >= 0 && rankIndex + rankIncrementer <= 7 && boardArr[rankIndex + rankIncrementer][fileIndex].piece == '.') {
					toReturn.push_back(boardArr[rankIndex + rankIncrementer][fileIndex].file + std::to_string(boardArr[rankIndex + rankIncrementer][fileIndex].rank));
				}
				else if (rankIndex + rankIncrementer >= 0 && rankIndex + rankIncrementer <= 7 && (isupper(boardArr[rankIndex + rankIncrementer][fileIndex].piece) == false) && boardArr[rankIndex + rankIncrementer][fileIndex].piece != '.') {
					toReturn.push_back(boardArr[rankIndex + rankIncrementer][fileIndex].file + std::to_string(boardArr[rankIndex + rankIncrementer][fileIndex].rank));
					break;
				}
				else if (rankIndex + rankIncrementer >= 0 && rankIndex + rankIncrementer <= 7 && (isupper(boardArr[rankIndex + rankIncrementer][fileIndex].piece) == true)) {
					break;
				}
			}
			else {
				if (rankIndex + rankIncrementer >= 0 && rankIndex + rankIncrementer <= 7 && boardArr[rankIndex + rankIncrementer][fileIndex].piece == '.') {
					toReturn.push_back(boardArr[rankIndex + rankIncrementer][fileIndex].file + std::to_string(boardArr[rankIndex + rankIncrementer][fileIndex].rank));
				}
				else if (rankIndex + rankIncrementer >= 0 && rankIndex + rankIncrementer <= 7 && (isupper(boardArr[rankIndex + rankIncrementer][fileIndex].piece) == true)) {
					toReturn.push_back(boardArr[rankIndex + rankIncrementer][fileIndex].file + std::to_string(boardArr[rankIndex + rankIncrementer][fileIndex].rank));
					break;
				}
				else if (rankIndex + rankIncrementer >= 0 && rankIndex + rankIncrementer <= 7 && (isupper(boardArr[rankIndex + rankIncrementer][fileIndex].piece) == false) && boardArr[rankIndex + rankIncrementer][fileIndex].piece != '.') {
					break;
				}
			}
		}

		for (int fileIncrementer = 1; fileIncrementer <= 8; fileIncrementer++) {
			if (pieceColor == "white") {
				if (fileIndex + fileIncrementer >= 0 && fileIndex + fileIncrementer <= 7 && boardArr[rankIndex][fileIndex + fileIncrementer].piece == '.') {
					toReturn.push_back(boardArr[rankIndex][fileIndex + fileIncrementer].file + std::to_string(boardArr[rankIndex][fileIndex + fileIncrementer].rank));
				}
				else if (fileIndex + fileIncrementer >= 0 && fileIndex + fileIncrementer <= 7 && (isupper(boardArr[rankIndex][fileIndex + fileIncrementer].piece) == false) && boardArr[rankIndex][fileIndex + fileIncrementer].piece != '.') {
					toReturn.push_back(boardArr[rankIndex][fileIndex + fileIncrementer].file + std::to_string(boardArr[rankIndex][fileIndex + fileIncrementer].rank));
					break;
				}
				else if (fileIndex + fileIncrementer >= 0 && fileIndex + fileIncrementer <= 7 && (isupper(boardArr[rankIndex][fileIndex + fileIncrementer].piece) == true)) {
					break;
				}
			}
			else {
				if (fileIndex + fileIncrementer >= 0 && fileIndex + fileIncrementer <= 7 && boardArr[rankIndex][fileIndex + fileIncrementer].piece == '.') {
					toReturn.push_back(boardArr[rankIndex][fileIndex + fileIncrementer].file + std::to_string(boardArr[rankIndex][fileIndex + fileIncrementer].rank));
				}
				else if (fileIndex + fileIncrementer >= 0 && fileIndex + fileIncrementer <= 7 && (isupper(boardArr[rankIndex][fileIndex + fileIncrementer].piece) == true)) {
					toReturn.push_back(boardArr[rankIndex][fileIndex + fileIncrementer].file + std::to_string(boardArr[rankIndex][fileIndex + fileIncrementer].rank));
					break;
				}
				else if (fileIndex + fileIncrementer >= 0 && fileIndex + fileIncrementer <= 7 && (isupper(boardArr[rankIndex][fileIndex + fileIncrementer].piece) == true) && boardArr[rankIndex][fileIndex + fileIncrementer].piece != '.') {
					break;
				}
			}
		}

		for (int fileIncrementer = -1; fileIncrementer >= -8; fileIncrementer--) {
			if (pieceColor == "white") {
				if (fileIndex + fileIncrementer >= 0 && fileIndex + fileIncrementer <= 7 && boardArr[rankIndex][fileIndex + fileIncrementer].piece == '.') {
					toReturn.push_back(boardArr[rankIndex][fileIndex + fileIncrementer].file + std::to_string(boardArr[rankIndex][fileIndex + fileIncrementer].rank));
				}
				else if (fileIndex + fileIncrementer >= 0 && fileIndex + fileIncrementer <= 7 && (isupper(boardArr[rankIndex][fileIndex + fileIncrementer].piece) == false) && boardArr[rankIndex][fileIndex + fileIncrementer].piece != '.') {
					toReturn.push_back(boardArr[rankIndex][fileIndex + fileIncrementer].file + std::to_string(boardArr[rankIndex][fileIndex + fileIncrementer].rank));
					break;
				}
				else if (fileIndex + fileIncrementer >= 0 && fileIndex + fileIncrementer <= 7 && (isupper(boardArr[rankIndex][fileIndex + fileIncrementer].piece) == true)) {
					break;
				}
			}
			else {
				if (fileIndex + fileIncrementer >= 0 && fileIndex + fileIncrementer <= 7 && boardArr[rankIndex][fileIndex + fileIncrementer].piece == '.') {
					toReturn.push_back(boardArr[rankIndex][fileIndex + fileIncrementer].file + std::to_string(boardArr[rankIndex][fileIndex + fileIncrementer].rank));
				}
				else if (fileIndex + fileIncrementer >= 0 && fileIndex + fileIncrementer <= 7 && (isupper(boardArr[rankIndex][fileIndex + fileIncrementer].piece) == true)) {
					toReturn.push_back(boardArr[rankIndex][fileIndex + fileIncrementer].file + std::to_string(boardArr[rankIndex][fileIndex + fileIncrementer].rank));
					break;
				}
				else if (fileIndex + fileIncrementer >= 0 && fileIndex + fileIncrementer <= 7 && (isupper(boardArr[rankIndex][fileIndex + fileIncrementer].piece) == false) && boardArr[rankIndex][fileIndex + fileIncrementer].piece != '.') {
					break;
				}
			}
		}
	}

	//KING
	else if (piece == 'k' || piece == 'K') {
		int fileIndArrK[8] = { fileIndex + 1, fileIndex + 1, fileIndex + 1, fileIndex, fileIndex - 1, fileIndex - 1, fileIndex - 1, fileIndex };
		int rankIndArrK[8] = { rankIndex - 1, rankIndex, rankIndex + 1, rankIndex + 1, rankIndex + 1, rankIndex, rankIndex - 1, rankIndex - 1 };
		if (pieceColor == "white") {
			for (int i = 0; i < 8; i++) {
				if (rankIndArrK[i] <= 7 && rankIndArrK[i] >= 0 && fileIndArrK[i] <= 7 && fileIndArrK[i] >= 0 && isupper(boardArr[rankIndArrK[i]][fileIndArrK[i]].piece) == false) {
					toReturn.push_back(boardArr[rankIndArrK[i]][fileIndArrK[i]].file + std::to_string(boardArr[rankIndArrK[i]][fileIndArrK[i]].rank));
				}
			}
		}
		else {
			for (int i = 0; i < 8; i++) {
				if (rankIndArrK[i] <= 7 && rankIndArrK[i] >= 0 && fileIndArrK[i] <= 7 && fileIndArrK[i] >= 0 && isupper(boardArr[rankIndArrK[i]][fileIndArrK[i]].piece) == true || boardArr[rankIndArrK[i]][fileIndArrK[i]].piece == '.') {
					toReturn.push_back(boardArr[rankIndArrK[i]][fileIndArrK[i]].file + std::to_string(boardArr[rankIndArrK[i]][fileIndArrK[i]].rank));
				}
			}
		}
	}

	//BISHOP
	else if (piece == 'b' || piece == 'B') {
		for (int i = 1; i < 8; i++) {
			if (pieceColor == "white") {
				if (rankIndex + i >= 0 && rankIndex + i <= 7 && fileIndex + i >= 0 && fileIndex + i <= 7 && boardArr[rankIndex + i][fileIndex + i].piece == '.') {
					toReturn.push_back(boardArr[rankIndex + i][fileIndex + i].file + std::to_string(boardArr[rankIndex + i][fileIndex + i].rank));
				}
				else if (rankIndex + i >= 0 && rankIndex + i <= 7 && fileIndex + i >= 0 && fileIndex + i <= 7 && (isupper(boardArr[rankIndex + i][fileIndex + i].piece) == false) && boardArr[rankIndex + i][fileIndex + i].piece != '.') {
					toReturn.push_back(boardArr[rankIndex + i][fileIndex + i].file + std::to_string(boardArr[rankIndex + i][fileIndex + i].rank));
					break;
				}
				else if (rankIndex + i >= 0 && rankIndex + i <= 7 && fileIndex + i >= 0 && fileIndex + i <= 7 && (isupper(boardArr[rankIndex + i][fileIndex + i].piece) == true)) {
					break;
				}
			}
			else {
				if (rankIndex + i >= 0 && rankIndex + i <= 7 && fileIndex + i >= 0 && fileIndex + i <= 7 && boardArr[rankIndex + i][fileIndex + i].piece == '.') {
					toReturn.push_back(boardArr[rankIndex + i][fileIndex + i].file + std::to_string(boardArr[rankIndex + i][fileIndex + i].rank));
				}
				else if (rankIndex + i >= 0 && rankIndex + i <= 7 && fileIndex + i >= 0 && fileIndex + i <= 7 && (isupper(boardArr[rankIndex + i][fileIndex + i].piece) == true)) {
					toReturn.push_back(boardArr[rankIndex + i][fileIndex + i].file + std::to_string(boardArr[rankIndex + i][fileIndex + i].rank));
					break;
				}
				else if (rankIndex + i >= 0 && rankIndex + i <= 7 && fileIndex + i >= 0 && fileIndex + i <= 7 && (isupper(boardArr[rankIndex + i][fileIndex + i].piece) == false) && boardArr[rankIndex + i][fileIndex + i].piece != '.') {
					break;
				}
			}
		}

		for (int i = 1; i < 8; i++) {
			if (pieceColor == "white") {
				if (rankIndex - i >= 0 && rankIndex - i <= 7 && fileIndex + i >= 0 && fileIndex + i <= 7 && boardArr[rankIndex - i][fileIndex + i].piece == '.') {
					toReturn.push_back(boardArr[rankIndex - i][fileIndex + i].file + std::to_string(boardArr[rankIndex - i][fileIndex + i].rank));
				}
				else if (rankIndex - i >= 0 && rankIndex - i <= 7 && fileIndex + i >= 0 && fileIndex + i <= 7 && (isupper(boardArr[rankIndex - i][fileIndex + i].piece) == false) && boardArr[rankIndex - i][fileIndex + i].piece != '.') {
					toReturn.push_back(boardArr[rankIndex - i][fileIndex + i].file + std::to_string(boardArr[rankIndex - i][fileIndex + i].rank));
					break;
				}
				else if (rankIndex - i >= 0 && rankIndex - i <= 7 && fileIndex + i >= 0 && fileIndex + i <= 7 && (isupper(boardArr[rankIndex - i][fileIndex + i].piece) == true)) {
					break;
				}
			}
			else {
				if (rankIndex - i >= 0 && rankIndex - i <= 7 && fileIndex + i >= 0 && fileIndex + i <= 7 && boardArr[rankIndex - i][fileIndex + i].piece == '.') {
					toReturn.push_back(boardArr[rankIndex - i][fileIndex + i].file + std::to_string(boardArr[rankIndex - i][fileIndex + i].rank));
				}
				else if (rankIndex - i >= 0 && rankIndex - i <= 7 && fileIndex + i >= 0 && fileIndex + i <= 7 && (isupper(boardArr[rankIndex - i][fileIndex + i].piece) == true)) {
					toReturn.push_back(boardArr[rankIndex - i][fileIndex + i].file + std::to_string(boardArr[rankIndex - i][fileIndex + i].rank));
					break;
				}
				else if (rankIndex - i >= 0 && rankIndex - i <= 7 && fileIndex + i >= 0 && fileIndex + i <= 7 && (isupper(boardArr[rankIndex - i][fileIndex + i].piece) == false) && boardArr[rankIndex - i][fileIndex + i].piece != '.') {
					break;
				}
			}
		}

		for (int i = 1; i < 8; i++) {
			if (pieceColor == "white") {
				if (rankIndex + i >= 0 && rankIndex + i <= 7 && fileIndex - i >= 0 && fileIndex - i <= 7 && boardArr[rankIndex + i][fileIndex - i].piece == '.') {
					toReturn.push_back(boardArr[rankIndex + i][fileIndex - i].file + std::to_string(boardArr[rankIndex + i][fileIndex - i].rank));
				}
				else if (rankIndex + i >= 0 && rankIndex + i <= 7 && fileIndex - i >= 0 && fileIndex - i <= 7 && (isupper(boardArr[rankIndex + i][fileIndex - i].piece) == false) && boardArr[rankIndex + i][fileIndex - i].piece != '.') {
					toReturn.push_back(boardArr[rankIndex + i][fileIndex - i].file + std::to_string(boardArr[rankIndex + i][fileIndex - i].rank));
					break;
				}
				else if (rankIndex + i >= 0 && rankIndex + i <= 7 && fileIndex - i >= 0 && fileIndex - i <= 7 && (isupper(boardArr[rankIndex + i][fileIndex - i].piece) == true)) {
					break;
				}
			}
			else {
				if (rankIndex + i >= 0 && rankIndex + i <= 7 && fileIndex - i >= 0 && fileIndex - i <= 7 && boardArr[rankIndex + i][fileIndex - i].piece == '.') {
					toReturn.push_back(boardArr[rankIndex + i][fileIndex - i].file + std::to_string(boardArr[rankIndex + i][fileIndex - i].rank));
				}
				else if (rankIndex + i >= 0 && rankIndex + i <= 7 && fileIndex - i >= 0 && fileIndex - i <= 7 && (isupper(boardArr[rankIndex + i][fileIndex - i].piece) == true)) {
					toReturn.push_back(boardArr[rankIndex + i][fileIndex - i].file + std::to_string(boardArr[rankIndex + i][fileIndex - i].rank));
					break;
				}
				else if (rankIndex + i >= 0 && rankIndex + i <= 7 && fileIndex - i >= 0 && fileIndex - i <= 7 && (isupper(boardArr[rankIndex + i][fileIndex - i].piece) == false) && boardArr[rankIndex + i][fileIndex - i].piece != '.') {
					break;
				}
			}
		}

		for (int i = 1; i < 8; i++) {
			if (pieceColor == "white") {
				if (rankIndex - i >= 0 && rankIndex - i <= 7 && fileIndex - i >= 0 && fileIndex - i <= 7 && boardArr[rankIndex - i][fileIndex - i].piece == '.') {
					toReturn.push_back(boardArr[rankIndex - i][fileIndex - i].file + std::to_string(boardArr[rankIndex - i][fileIndex - i].rank));
				}
				else if (rankIndex - i >= 0 && rankIndex - i <= 7 && fileIndex - i >= 0 && fileIndex - i <= 7 && (isupper(boardArr[rankIndex - i][fileIndex - i].piece) == false) && boardArr[rankIndex - i][fileIndex - i].piece != '.') {
					toReturn.push_back(boardArr[rankIndex - i][fileIndex - i].file + std::to_string(boardArr[rankIndex - i][fileIndex - i].rank));
					break;
				}
				else if (rankIndex - i >= 0 && rankIndex - i <= 7 && fileIndex - i >= 0 && fileIndex - i <= 7 && (isupper(boardArr[rankIndex - i][fileIndex - i].piece) == true)) {
					break;
				}
			}
			else {
				if (rankIndex - i >= 0 && rankIndex - i <= 7 && fileIndex - i >= 0 && fileIndex - i <= 7 && boardArr[rankIndex - i][fileIndex - i].piece == '.') {
					toReturn.push_back(boardArr[rankIndex - i][fileIndex - i].file + std::to_string(boardArr[rankIndex - i][fileIndex - i].rank));
				}
				else if (rankIndex - i >= 0 && rankIndex - i <= 7 && fileIndex - i >= 0 && fileIndex - i <= 7 && (isupper(boardArr[rankIndex - i][fileIndex - i].piece) == true)) {
					toReturn.push_back(boardArr[rankIndex - i][fileIndex - i].file + std::to_string(boardArr[rankIndex - i][fileIndex - i].rank));
					break;
				}
				else if (rankIndex - i >= 0 && rankIndex - i <= 7 && fileIndex - i >= 0 && fileIndex - i <= 7 && (isupper(boardArr[rankIndex - i][fileIndex - i].piece) == false) && boardArr[rankIndex - i][fileIndex - i].piece != '.') {
					break;
				}
			}
		}
	}

	//QUEEN
	else if (piece == 'q' || piece == 'Q') {
		for (int rankIncrementer = 1; rankIncrementer <= 8; rankIncrementer++) {
			if (pieceColor == "white") {
				if (rankIndex + rankIncrementer >= 0 && rankIndex + rankIncrementer <= 7 && boardArr[rankIndex + rankIncrementer][fileIndex].piece == '.') {
					toReturn.push_back(boardArr[rankIndex + rankIncrementer][fileIndex].file + std::to_string(boardArr[rankIndex + rankIncrementer][fileIndex].rank));
				}
				else if (rankIndex + rankIncrementer >= 0 && rankIndex + rankIncrementer <= 7 && (isupper(boardArr[rankIndex + rankIncrementer][fileIndex].piece) == false) && boardArr[rankIndex + rankIncrementer][fileIndex].piece != '.') {
					toReturn.push_back(boardArr[rankIndex + rankIncrementer][fileIndex].file + std::to_string(boardArr[rankIndex + rankIncrementer][fileIndex].rank));
					break;
				}
				else if (rankIndex + rankIncrementer >= 0 && rankIndex + rankIncrementer <= 7 && (isupper(boardArr[rankIndex + rankIncrementer][fileIndex].piece) == true)) {
					break;
				}
			}
			else {
				if (rankIndex + rankIncrementer >= 0 && rankIndex + rankIncrementer <= 7 && boardArr[rankIndex + rankIncrementer][fileIndex].piece == '.') {
					toReturn.push_back(boardArr[rankIndex + rankIncrementer][fileIndex].file + std::to_string(boardArr[rankIndex + rankIncrementer][fileIndex].rank));
				}
				else if (rankIndex + rankIncrementer >= 0 && rankIndex + rankIncrementer <= 7 && (isupper(boardArr[rankIndex + rankIncrementer][fileIndex].piece) == true)) {
					toReturn.push_back(boardArr[rankIndex + rankIncrementer][fileIndex].file + std::to_string(boardArr[rankIndex + rankIncrementer][fileIndex].rank));
					break;
				}
				else if (rankIndex + rankIncrementer >= 0 && rankIndex + rankIncrementer <= 7 && (isupper(boardArr[rankIndex + rankIncrementer][fileIndex].piece) == false) && boardArr[rankIndex + rankIncrementer][fileIndex].piece != '.') {
					break;
				}
			}
		}

		for (int rankIncrementer = -1; rankIncrementer >= -8; rankIncrementer--) {
			if (pieceColor == "white") {
				if (rankIndex + rankIncrementer >= 0 && rankIndex + rankIncrementer <= 7 && boardArr[rankIndex + rankIncrementer][fileIndex].piece == '.') {
					toReturn.push_back(boardArr[rankIndex + rankIncrementer][fileIndex].file + std::to_string(boardArr[rankIndex + rankIncrementer][fileIndex].rank));
				}
				else if (rankIndex + rankIncrementer >= 0 && rankIndex + rankIncrementer <= 7 && (isupper(boardArr[rankIndex + rankIncrementer][fileIndex].piece) == false) && boardArr[rankIndex + rankIncrementer][fileIndex].piece != '.') {
					toReturn.push_back(boardArr[rankIndex + rankIncrementer][fileIndex].file + std::to_string(boardArr[rankIndex + rankIncrementer][fileIndex].rank));
					break;
				}
				else if (rankIndex + rankIncrementer >= 0 && rankIndex + rankIncrementer <= 7 && (isupper(boardArr[rankIndex + rankIncrementer][fileIndex].piece) == true)) {
					break;
				}
			}
			else {
				if (rankIndex + rankIncrementer >= 0 && rankIndex + rankIncrementer <= 7 && boardArr[rankIndex + rankIncrementer][fileIndex].piece == '.') {
					toReturn.push_back(boardArr[rankIndex + rankIncrementer][fileIndex].file + std::to_string(boardArr[rankIndex + rankIncrementer][fileIndex].rank));
				}
				else if (rankIndex + rankIncrementer >= 0 && rankIndex + rankIncrementer <= 7 && (isupper(boardArr[rankIndex + rankIncrementer][fileIndex].piece) == true)) {
					toReturn.push_back(boardArr[rankIndex + rankIncrementer][fileIndex].file + std::to_string(boardArr[rankIndex + rankIncrementer][fileIndex].rank));
					break;
				}
				else if (rankIndex + rankIncrementer >= 0 && rankIndex + rankIncrementer <= 7 && (isupper(boardArr[rankIndex + rankIncrementer][fileIndex].piece) == false) && boardArr[rankIndex + rankIncrementer][fileIndex].piece != '.') {
					break;
				}
			}
		}

		for (int fileIncrementer = 1; fileIncrementer <= 8; fileIncrementer++) {
			if (pieceColor == "white") {
				if (fileIndex + fileIncrementer >= 0 && fileIndex + fileIncrementer <= 7 && boardArr[rankIndex][fileIndex + fileIncrementer].piece == '.') {
					toReturn.push_back(boardArr[rankIndex][fileIndex + fileIncrementer].file + std::to_string(boardArr[rankIndex][fileIndex + fileIncrementer].rank));
				}
				else if (fileIndex + fileIncrementer >= 0 && fileIndex + fileIncrementer <= 7 && (isupper(boardArr[rankIndex][fileIndex + fileIncrementer].piece) == false) && boardArr[rankIndex][fileIndex + fileIncrementer].piece != '.') {
					toReturn.push_back(boardArr[rankIndex][fileIndex + fileIncrementer].file + std::to_string(boardArr[rankIndex][fileIndex + fileIncrementer].rank));
					break;
				}
				else if (fileIndex + fileIncrementer >= 0 && fileIndex + fileIncrementer <= 7 && (isupper(boardArr[rankIndex][fileIndex + fileIncrementer].piece) == true)) {
					break;
				}
			}
			else {
				if (fileIndex + fileIncrementer >= 0 && fileIndex + fileIncrementer <= 7 && boardArr[rankIndex][fileIndex + fileIncrementer].piece == '.') {
					toReturn.push_back(boardArr[rankIndex][fileIndex + fileIncrementer].file + std::to_string(boardArr[rankIndex][fileIndex + fileIncrementer].rank));
				}
				else if (fileIndex + fileIncrementer >= 0 && fileIndex + fileIncrementer <= 7 && (isupper(boardArr[rankIndex][fileIndex + fileIncrementer].piece) == true)) {
					toReturn.push_back(boardArr[rankIndex][fileIndex + fileIncrementer].file + std::to_string(boardArr[rankIndex][fileIndex + fileIncrementer].rank));
					break;
				}
				else if (fileIndex + fileIncrementer >= 0 && fileIndex + fileIncrementer <= 7 && (isupper(boardArr[rankIndex][fileIndex + fileIncrementer].piece) == true) && boardArr[rankIndex][fileIndex + fileIncrementer].piece != '.') {
					break;
				}
			}
		}

		for (int fileIncrementer = -1; fileIncrementer >= -8; fileIncrementer--) {
			if (pieceColor == "white") {
				if (fileIndex + fileIncrementer >= 0 && fileIndex + fileIncrementer <= 7 && boardArr[rankIndex][fileIndex + fileIncrementer].piece == '.') {
					toReturn.push_back(boardArr[rankIndex][fileIndex + fileIncrementer].file + std::to_string(boardArr[rankIndex][fileIndex + fileIncrementer].rank));
				}
				else if (fileIndex + fileIncrementer >= 0 && fileIndex + fileIncrementer <= 7 && (isupper(boardArr[rankIndex][fileIndex + fileIncrementer].piece) == false) && boardArr[rankIndex][fileIndex + fileIncrementer].piece != '.') {
					toReturn.push_back(boardArr[rankIndex][fileIndex + fileIncrementer].file + std::to_string(boardArr[rankIndex][fileIndex + fileIncrementer].rank));
					break;
				}
				else if (fileIndex + fileIncrementer >= 0 && fileIndex + fileIncrementer <= 7 && (isupper(boardArr[rankIndex][fileIndex + fileIncrementer].piece) == true)) {
					break;
				}
			}
			else {
				if (fileIndex + fileIncrementer >= 0 && fileIndex + fileIncrementer <= 7 && boardArr[rankIndex][fileIndex + fileIncrementer].piece == '.') {
					toReturn.push_back(boardArr[rankIndex][fileIndex + fileIncrementer].file + std::to_string(boardArr[rankIndex][fileIndex + fileIncrementer].rank));
				}
				else if (fileIndex + fileIncrementer >= 0 && fileIndex + fileIncrementer <= 7 && (isupper(boardArr[rankIndex][fileIndex + fileIncrementer].piece) == true)) {
					toReturn.push_back(boardArr[rankIndex][fileIndex + fileIncrementer].file + std::to_string(boardArr[rankIndex][fileIndex + fileIncrementer].rank));
					break;
				}
				else if (fileIndex + fileIncrementer >= 0 && fileIndex + fileIncrementer <= 7 && (isupper(boardArr[rankIndex][fileIndex + fileIncrementer].piece) == false) && boardArr[rankIndex][fileIndex + fileIncrementer].piece != '.') {
					break;
				}
			}
		}

		for (int i = 1; i < 8; i++) {
			if (pieceColor == "white") {
				if (rankIndex + i >= 0 && rankIndex + i <= 7 && fileIndex + i >= 0 && fileIndex + i <= 7 && boardArr[rankIndex + i][fileIndex + i].piece == '.') {
					toReturn.push_back(boardArr[rankIndex + i][fileIndex + i].file + std::to_string(boardArr[rankIndex + i][fileIndex + i].rank));
				}
				else if (rankIndex + i >= 0 && rankIndex + i <= 7 && fileIndex + i >= 0 && fileIndex + i <= 7 && (isupper(boardArr[rankIndex + i][fileIndex + i].piece) == false) && boardArr[rankIndex + i][fileIndex + i].piece != '.') {
					toReturn.push_back(boardArr[rankIndex + i][fileIndex + i].file + std::to_string(boardArr[rankIndex + i][fileIndex + i].rank));
					break;
				}
				else if (rankIndex + i >= 0 && rankIndex + i <= 7 && fileIndex + i >= 0 && fileIndex + i <= 7 && (isupper(boardArr[rankIndex + i][fileIndex + i].piece) == true)) {
					break;
				}
			}
			else {
				if (rankIndex + i >= 0 && rankIndex + i <= 7 && fileIndex + i >= 0 && fileIndex + i <= 7 && boardArr[rankIndex + i][fileIndex + i].piece == '.') {
					toReturn.push_back(boardArr[rankIndex + i][fileIndex + i].file + std::to_string(boardArr[rankIndex + i][fileIndex + i].rank));
				}
				else if (rankIndex + i >= 0 && rankIndex + i <= 7 && fileIndex + i >= 0 && fileIndex + i <= 7 && (isupper(boardArr[rankIndex + i][fileIndex + i].piece) == true)) {
					toReturn.push_back(boardArr[rankIndex + i][fileIndex + i].file + std::to_string(boardArr[rankIndex + i][fileIndex + i].rank));
					break;
				}
				else if (rankIndex + i >= 0 && rankIndex + i <= 7 && fileIndex + i >= 0 && fileIndex + i <= 7 && (isupper(boardArr[rankIndex + i][fileIndex + i].piece) == false) && boardArr[rankIndex + i][fileIndex + i].piece != '.') {
					break;
				}
			}
		}

		for (int i = 1; i < 8; i++) {
			if (pieceColor == "white") {
				if (rankIndex - i >= 0 && rankIndex - i <= 7 && fileIndex + i >= 0 && fileIndex + i <= 7 && boardArr[rankIndex - i][fileIndex + i].piece == '.') {
					toReturn.push_back(boardArr[rankIndex - i][fileIndex + i].file + std::to_string(boardArr[rankIndex - i][fileIndex + i].rank));
				}
				else if (rankIndex - i >= 0 && rankIndex - i <= 7 && fileIndex + i >= 0 && fileIndex + i <= 7 && (isupper(boardArr[rankIndex - i][fileIndex + i].piece) == false) && boardArr[rankIndex - i][fileIndex + i].piece != '.') {
					toReturn.push_back(boardArr[rankIndex - i][fileIndex + i].file + std::to_string(boardArr[rankIndex - i][fileIndex + i].rank));
					break;
				}
				else if (rankIndex - i >= 0 && rankIndex - i <= 7 && fileIndex + i >= 0 && fileIndex + i <= 7 && (isupper(boardArr[rankIndex - i][fileIndex + i].piece) == true)) {
					break;
				}
			}
			else {
				if (rankIndex - i >= 0 && rankIndex - i <= 7 && fileIndex + i >= 0 && fileIndex + i <= 7 && boardArr[rankIndex - i][fileIndex + i].piece == '.') {
					toReturn.push_back(boardArr[rankIndex - i][fileIndex + i].file + std::to_string(boardArr[rankIndex - i][fileIndex + i].rank));
				}
				else if (rankIndex - i >= 0 && rankIndex - i <= 7 && fileIndex + i >= 0 && fileIndex + i <= 7 && (isupper(boardArr[rankIndex - i][fileIndex + i].piece) == true)) {
					toReturn.push_back(boardArr[rankIndex - i][fileIndex + i].file + std::to_string(boardArr[rankIndex - i][fileIndex + i].rank));
					break;
				}
				else if (rankIndex - i >= 0 && rankIndex - i <= 7 && fileIndex + i >= 0 && fileIndex + i <= 7 && (isupper(boardArr[rankIndex - i][fileIndex + i].piece) == false) && boardArr[rankIndex - i][fileIndex + i].piece != '.') {
					break;
				}
			}
		}

		for (int i = 1; i < 8; i++) {
			if (pieceColor == "white") {
				if (rankIndex + i >= 0 && rankIndex + i <= 7 && fileIndex - i >= 0 && fileIndex - i <= 7 && boardArr[rankIndex + i][fileIndex - i].piece == '.') {
					toReturn.push_back(boardArr[rankIndex + i][fileIndex - i].file + std::to_string(boardArr[rankIndex + i][fileIndex - i].rank));
				}
				else if (rankIndex + i >= 0 && rankIndex + i <= 7 && fileIndex - i >= 0 && fileIndex - i <= 7 && (isupper(boardArr[rankIndex + i][fileIndex - i].piece) == false) && boardArr[rankIndex + i][fileIndex - i].piece != '.') {
					toReturn.push_back(boardArr[rankIndex + i][fileIndex - i].file + std::to_string(boardArr[rankIndex + i][fileIndex - i].rank));
					break;
				}
				else if (rankIndex + i >= 0 && rankIndex + i <= 7 && fileIndex - i >= 0 && fileIndex - i <= 7 && (isupper(boardArr[rankIndex + i][fileIndex - i].piece) == true)) {
					break;
				}
			}
			else {
				if (rankIndex + i >= 0 && rankIndex + i <= 7 && fileIndex - i >= 0 && fileIndex - i <= 7 && boardArr[rankIndex + i][fileIndex - i].piece == '.') {
					toReturn.push_back(boardArr[rankIndex + i][fileIndex - i].file + std::to_string(boardArr[rankIndex + i][fileIndex - i].rank));
				}
				else if (rankIndex + i >= 0 && rankIndex + i <= 7 && fileIndex - i >= 0 && fileIndex - i <= 7 && (isupper(boardArr[rankIndex + i][fileIndex - i].piece) == true)) {
					toReturn.push_back(boardArr[rankIndex + i][fileIndex - i].file + std::to_string(boardArr[rankIndex + i][fileIndex - i].rank));
					break;
				}
				else if (rankIndex + i >= 0 && rankIndex + i <= 7 && fileIndex - i >= 0 && fileIndex - i <= 7 && (isupper(boardArr[rankIndex + i][fileIndex - i].piece) == false) && boardArr[rankIndex + i][fileIndex - i].piece != '.') {
					break;
				}
			}
		}

		for (int i = 1; i < 8; i++) {
			if (pieceColor == "white") {
				if (rankIndex - i >= 0 && rankIndex - i <= 7 && fileIndex - i >= 0 && fileIndex - i <= 7 && boardArr[rankIndex - i][fileIndex - i].piece == '.') {
					toReturn.push_back(boardArr[rankIndex - i][fileIndex - i].file + std::to_string(boardArr[rankIndex - i][fileIndex - i].rank));
				}
				else if (rankIndex - i >= 0 && rankIndex - i <= 7 && fileIndex - i >= 0 && fileIndex - i <= 7 && (isupper(boardArr[rankIndex - i][fileIndex - i].piece) == false) && boardArr[rankIndex - i][fileIndex - i].piece != '.') {
					toReturn.push_back(boardArr[rankIndex - i][fileIndex - i].file + std::to_string(boardArr[rankIndex - i][fileIndex - i].rank));
					break;
				}
				else if (rankIndex - i >= 0 && rankIndex - i <= 7 && fileIndex - i >= 0 && fileIndex - i <= 7 && (isupper(boardArr[rankIndex - i][fileIndex - i].piece) == true)) {
					break;
				}
			}
			else {
				if (rankIndex - i >= 0 && rankIndex - i <= 7 && fileIndex - i >= 0 && fileIndex - i <= 7 && boardArr[rankIndex - i][fileIndex - i].piece == '.') {
					toReturn.push_back(boardArr[rankIndex - i][fileIndex - i].file + std::to_string(boardArr[rankIndex - i][fileIndex - i].rank));
				}
				else if (rankIndex - i >= 0 && rankIndex - i <= 7 && fileIndex - i >= 0 && fileIndex - i <= 7 && (isupper(boardArr[rankIndex - i][fileIndex - i].piece) == true)) {
					toReturn.push_back(boardArr[rankIndex - i][fileIndex - i].file + std::to_string(boardArr[rankIndex - i][fileIndex - i].rank));
					break;
				}
				else if (rankIndex - i >= 0 && rankIndex - i <= 7 && fileIndex - i >= 0 && fileIndex - i <= 7 && (isupper(boardArr[rankIndex - i][fileIndex - i].piece) == false) && boardArr[rankIndex - i][fileIndex - i].piece != '.') {
					break;
				}
			}
		}
	}

	return toReturn;
}