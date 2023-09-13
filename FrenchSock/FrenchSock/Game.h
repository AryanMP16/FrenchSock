#ifndef GAME_H
#define GAME_H

class Board;
class Player;

class Game {
private:
	Board* board;
	Player* whitePlayer;
	Player* blackPlayer;
public:
	Game(Board* inp_board, Player* inp_whitePlayer, Player* inp_blackPlayer) : board(inp_board), whitePlayer(inp_whitePlayer), blackPlayer(inp_blackPlayer) {}
	void play() const;
};

#endif