#include <iostream>
#include <cassert>
#include "Board.h"
#include "Player.h"
#include "Game.h"

int main() {
	Board board;
	Human_Player whitePlayer("Human", "white", &board);
	AI_Player blackPlayer("AI", "black", &board);

	board.viewBoard();
	
	Game game(&board, &whitePlayer, &blackPlayer);

	game.play();

	return 0;
}