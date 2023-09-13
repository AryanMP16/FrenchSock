#include "Game.h"
#include "Board.h"
#include "Player.h"
#include <iostream>

void Game::play() const {
	for (int i = 0; i < 10; i++) {
		if (i % 2 == 0) {
			board->makeMove(whitePlayer->chooseMove());
		}
		else {
			board->makeMove(blackPlayer->chooseMove());
		}

		///////////////FOR TESTING://////////////
		std::cout << std::endl;
		(*board).viewBoard();
		std::cout << std::endl;
		/////////////^^FOR TESTING://////////////
	}
}