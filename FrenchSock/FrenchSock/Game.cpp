#include "Game.h"
#include "Board.h"
#include "Player.h"
#include <iostream>

void Game::play() const {
	for (int i = 0; i < 100; i++) {
		std::string chosenMove;

		if (i % 2 == 0) {
			chosenMove = whitePlayer->chooseMove();
			board->makeMove(chosenMove);

			/*std::cout << std::endl;
			std::cout << chosenMove;
			std::cout << std::endl;*/
		}
		else {
			chosenMove = blackPlayer->chooseMove();
			board->makeMove(chosenMove);
		}

		///////////////FOR TESTING://////////////
		std::cout << std::endl;
		(*board).viewBoard();
		std::cout << std::endl;
		/////////////^^FOR TESTING://////////////
	}
}