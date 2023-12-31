#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include "Board.h"

class Player {
public:
	Player(std::string name, std::string side, Board* board) : playerName(name), playerSide(side), playerBoard(board) {}
	virtual std::string chooseMove() = 0;
	std::string side() { return playerSide; }
	std::string name() { return playerName; }
protected:
	std::string playerName;
	std::string playerSide;
	Board* playerBoard;
};

class AI_Player : public Player {
private:
	struct move {
		std::string algebraicMove;
		double eval;
	};
public:
	AI_Player(std::string name, std::string side, Board* board) : Player(name, side, board) {}
	std::string chooseMove();
	move chooseMoveHelper(int depth, std::string maximizingPlayer, Board currBoardPtr, std::string moveMadeToGetHere = "/////");
};

class Bad_AI_Player : public Player {
public:
	Bad_AI_Player(std::string name, std::string side, Board* board) : Player(name, side, board) {}
	std::string chooseMove();
};

class Human_Player : public Player {
public:
	Human_Player(std::string name, std::string side, Board* board) : Player(name, side, board) {}
	std::string chooseMove();
};

#endif