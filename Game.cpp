#include "Game.h"
#include "Exceptions.h"
#include "Pipe.h"
#include <string>
#include <iostream>
#include <thread>


Game::Game()
{
	isConnect = p.connect();
}

Game::~Game(){}

void Game::startGame()
{
	std::string ans;
	std::string msgFromGraph;

	while (!isConnect)
	{
		std::cout << "cant connect to graphics" << std::endl;
		std::cout << "Do you want to try to connect again or exit? (0-try again, 1-exit)" << std::endl;
		std::cin >> ans;

		if (ans == "0")
		{
			std::cout << "trying connect again.." << std::endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else
		{
			p.close();
			return;
		}

	}

	strcpy_s(_starterBoard, "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR1");
	p.sendMessageToGraphics(_starterBoard);
	msgFromGraph = p.getMessageFromGraphics();
	while (msgFromGraph != "quit")
	{
		std::string start;
		std::string end;
			
		//getting the first 2 letters
		start = msgFromGraph.substr(0, 2);

		//getting the rest
		end = msgFromGraph.substr(2);
			
		validateMove(start, end);
	}

	p.close();
}

std::string Game::validateMove(std::string start, std::string end)
{
	int validCode = isMoveValid(start, end);
	std::string ans;
	sendMsg[0] = '0' + validCode;
	sendMsg[1] = '\0';

	if(validCode == 0 || validCode==8)
	{
		executeMove(start, end);
	}

	p.sendMessageToGraphics(sendMsg);
	ans = p.getMessageFromGraphics();
	return ans;
}

std::string Game::executeMove(std::string start, std::string end)
{
	try
	{
		Board::movePiece(start, end);
		playerTurn.switchTurn();
		return "success";
		
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return e.what();
	}
}
