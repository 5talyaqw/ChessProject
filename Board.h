#pragma once
#include <string>
#include "Piece.h"
class Piece;

class Board
{
protected:
	Piece* cur;
	char _board[8][8];

public:
	Board();
	int isMoveValid(std::string start, std::string end);
	bool isKingCheck(std::string kingPos, std::string pcolor);

	bool isPieceAttackingKing(int startRow, int startCol, int kingRow, int kingCol, char piece);
	bool isRookAttacking(int startRow, int startCol, int kingRow, int kingCol);
	bool isPawnAttacking(int startRow, int startCol, int kingRow, int kingCol);
	bool isBishopAttacking(int startRow, int startCol, int kingRow, int kingCol);
	bool isQueenAttacking(int startRow, int startCol, int kingRow, int kingCol);
	bool isKnightAttacking(int startRow, int startCol, int kingRow, int kingCol);

	void movePiece(std::string start, std::string end);
	bool isCheckMate(std::string color);

};

