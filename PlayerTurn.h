#pragma once
#include <iostream>
class PlayerTurn
{
private:
    std::string _playerTurn;
public:
    PlayerTurn();
    std::string getTurn() const;
    void switchTurn();
};

