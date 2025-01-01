#pragma once
#include "Board.h"

class Board;

class Piece : public Board
{
protected:
	std::string _color;
	std::string _symbol; // 'K' or 'k' for example

public:
	Piece(std::string color, std::string symbol);

	virtual bool canMove(int startRow, int startCol, int endRow, int endCol) = 0;

	std::string getColor() const;
	std::string getSymbol() const;
};

class King : public Piece
{
public:
	King(std::string color, std::string symbol);
	bool canMove(int startRow, int startCol, int endRow, int endCol);
};
    
class Queen : public Piece
{
public:
	Queen(std::string color, std::string symbol);
	bool canMove(int startRow, int startCol, int endRow, int endCol);
};

class Pawn : public Piece
{
public:
	Pawn(std::string color, std::string symbol);
	bool canMove(int startRow, int startCol, int endRow, int EndCol);
};

class Bishop : public Piece
{
public:
	Bishop(std::string color, std::string symbol);
	bool canMove(int startRow, int startCol, int endRow, int endCol);
};

class Knight : public Piece
{
public:
	Knight(std::string color, std::string symbol);
	bool canMove(int startRow, int startCol, int endRow, int endCol);
};

class Rook : public Piece
{
public:
	Rook(std::string color, std::string symbol);
	bool canMove(int startRow, int startCol, int endRow, int endCol);
};