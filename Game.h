#pragma once
#include "Board.h"
#include "PlayerTurn.h"
#include "Pipe.h"
#include <string>
class Game : public Board
{
private:
	char  _starterBoard[1024];
	Pipe p;
	char sendMsg[2];
	bool isConnect;
	
public:
	Game();
	~Game();
	void startGame();
	std::string validateMove(std::string start, std::string end);
	std::string executeMove(std::string start, std::string end);
};

