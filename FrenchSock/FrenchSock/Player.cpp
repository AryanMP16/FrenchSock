#include "Player.h"
#include <iostream>

std::string Bad_AI_Player::chooseMove() { //choses the first legal move for the first piece of that color found. Has bias towards pieces on bottom left
	std::vector<Board::square> piecesRemaining;
	std::vector<std::string> legalMoves;
	playerSide == "white" ? piecesRemaining = playerBoard->piecesLeft("white") : piecesRemaining = playerBoard->piecesLeft("black");
	for (int i = 0; i < piecesRemaining.size(); i++) {
		legalMoves = playerBoard->legalMoves(piecesRemaining[i].file + std::to_string(piecesRemaining[i].rank));
		if (legalMoves.size() != 0) {
			return piecesRemaining[i].file + std::to_string(piecesRemaining[i].rank) + ":" + legalMoves[0];
		}
	}
}

std::string AI_Player::chooseMove() {
	move chosenMove = chooseMoveHelper(2, playerSide, *playerBoard);
	return chosenMove.algebraicMove;
}

AI_Player::move AI_Player::chooseMoveHelper(int depth, std::string maximizingPlayer, Board currBoard, std::string moveMadeToGetHere /*null move*/) { //the "actual AI" algorithm
	//initializing current node -- O(1)
	move currentNode{moveMadeToGetHere, currBoard.evaluatePosition()};
																			
	//creting a copy of the board so we don't mess up the actual board
	Board boardCpy = currBoard;

	//determine remaining pieces based on color -- O(1)
	std::vector<Board::square> piecesRemaining;
	maximizingPlayer == "white" ? piecesRemaining = playerBoard->piecesLeft("white") : piecesRemaining = playerBoard->piecesLeft("black");

	//base case -- O(1)
	if (depth == 0 /*OR checkmate, which hasn't been coded in yet*/)
		return currentNode;

	if (maximizingPlayer == "white") {
		move maxEvalMove{ "/////", -999999999 };
		for (int piece = 0; piece < piecesRemaining.size(); piece++) {
			std::string squareOfPiece = piecesRemaining[piece].file + std::to_string(piecesRemaining[piece].rank);
			std::vector<std::string> moves = playerBoard->legalMoves(squareOfPiece);
			for (int i = 0; i < moves.size(); i++) {
				boardCpy.makeMove(squareOfPiece + ":" + moves[i]);
				move nextEval{squareOfPiece + ":" + moves[i], chooseMoveHelper(depth - 1, "black", boardCpy, squareOfPiece + ":" + moves[i]).eval};
				if (nextEval.eval > maxEvalMove.eval)
					maxEvalMove = nextEval;
				boardCpy.makeMove(moves[i] + ":" + squareOfPiece);
			}
		}
		return maxEvalMove;
	}
	else {
		move minEvalMove{ "/////", 999999999 };
		for (int piece = 0; piece < piecesRemaining.size(); piece++) {
			std::string squareOfPiece = piecesRemaining[piece].file + std::to_string(piecesRemaining[piece].rank);
			std::vector<std::string> moves = playerBoard->legalMoves(squareOfPiece);
			for (int i = 0; i < moves.size(); i++) {
				boardCpy.makeMove(squareOfPiece + ":" + moves[i]);
				move nextEval{ squareOfPiece + ":" + moves[i], chooseMoveHelper(depth - 1, "white", boardCpy, squareOfPiece + ":" + moves[i]).eval };
				if (nextEval.eval < minEvalMove.eval)
					minEvalMove = nextEval;
				boardCpy.makeMove(moves[i] + ":" + squareOfPiece);
			}
		}
		return minEvalMove;
	}

}

std::string Human_Player::chooseMove() {
	std::string toReturn;
	std::cout << std::endl << "Type in a move:\t";
	std::cin >> toReturn;
	return toReturn;
}