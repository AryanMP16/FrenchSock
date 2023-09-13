#include <iostream>
#include <cassert>
#include "Board.h"
#include "Player.h"
#include "Game.h"

int main() {
	Board board;
	AI_Player whitePlayer("AI", "white", &board);
	AI_Player blackPlayer("AI", "black", &board);
	
	Game game(&board, &whitePlayer, &blackPlayer);

	game.play();

	return 0;
}