#include "PlayerTurn.h"

PlayerTurn::PlayerTurn()
{
    _playerTurn = "black";
}

std::string PlayerTurn::getTurn() const
{
	return _playerTurn;
}

void PlayerTurn::switchTurn()
{
    if(_playerTurn == "White")
    {
        _playerTurn = "Black";
    }
    else
    {
        _playerTurn = "White";
    }
}
