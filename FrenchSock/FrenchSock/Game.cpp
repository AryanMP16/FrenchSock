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
		}
		else {
			chosenMove = blackPlayer->chooseMove();

			if (blackPlayer->name() == "AI" && i == 1) {
				if (board->viewSquare(3, 4).piece == 'P')
					chosenMove = "e7:e5";
				else
					chosenMove = "d7:d5";
			}

			board->makeMove(chosenMove);

			std::cout << std::endl;
			std::cout << chosenMove;
			std::cout << std::endl;
		}

		///////////////FOR TESTING://////////////
		/*std::cout << std::endl;
		(*board).viewBoard();
		std::cout << std::endl;*/
		/////////////^^FOR TESTING://////////////
	}
}