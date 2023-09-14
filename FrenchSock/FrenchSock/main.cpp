#include <iostream>
#include <cassert>
#include "Board.h"
#include "Player.h"
#include "Game.h"

int main() {
	Board board;
	Human_Player blackPlayer("Human", "black", &board);
	AI_Player whitePlayer("AI", "white", &board);

	board.viewBoard();
	
	Game game(&board, &whitePlayer, &blackPlayer);

	game.play();

	return 0;
}