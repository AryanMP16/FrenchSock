#include <iostream>
#include <cassert>
#include "Board.h"
#include "Player.h"
#include "Game.h"

int main() {
	Board board;
	Human_Player whitePlayer("Human", "white", &board);
	AI_Player blackPlayer("AI", "black", &board);

	board.makeMove("e2:e4");
	board.makeMove("d7:d5");
	board.makeMove("e4:d5");
	board.makeMove("d8:d5");
	board.makeMove("b1:c3");

	board.viewBoard();

	std::cout << blackPlayer.chooseMove();
	
	/*Game game(&board, &whitePlayer, &blackPlayer);

	game.play();*/

	return 0;
}