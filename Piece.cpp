#include "Piece.h"
#include "Exceptions.h"

Piece::Piece(std::string color, std::string symbol) : _color(color), _symbol(symbol) {}


// Getters
std::string Piece::getColor() const
{
	return _color;
}

std::string Piece::getSymbol() const
{
	return _symbol;
}

// King's methods
King::King(std::string color, std::string symbol) : Piece::Piece(color, symbol)
{
}

bool King::canMove(int startRow, int startCol, int endRow, int endCol)
{
	int dx = abs(endCol - startCol);
	int dy = abs(endRow - startRow);
	if (dx <= 1 && dy <= 1) {
		return true; // King moves one square in any direction
	}
	throw illegalMovement();
	return false;
}

// Queen's methods
Queen::Queen(std::string color, std::string symbol) : Piece::Piece(color, symbol)
{
}

bool Queen::canMove(int startRow, int startCol, int endRow, int endCol)
{
	//rook
	if (startCol == endCol || startRow == endRow)
	{
		if (startCol == endCol) // Moving vertically
		{
			int step = (endRow > startRow) ? 1 : -1;
			for (int i = startRow + step; i != endRow; i += step)
			{
				if (_board[startCol][i] != '#') // Blocked by a piece
				{
					throw PieceInDst();
					return false;
				}
				return true;
			}
		}
		if (startRow == endRow) // Moving horizontally
		{
			int step = (endCol > startCol) ? 1 : -1;
			for (int i = startCol + step; i != endCol; i += step)
			{
				if (_board[i][startRow] != '#') // Blocked by a piece
				{
					throw PieceInDst();
					return false;
				}
			}
			return true;
		}	
	}
	//bishop
	if (abs(endCol - startCol) == abs(endRow - startRow))
	{
		int dx = (endCol > startCol) ? 1 : -1;
		int dy = (endRow > startRow) ? 1 : -1;
		int x = startCol + dx;
		int y = startRow + dy;

		while (x != endCol && y != endRow)
		{
			if (_board[x][y] != '#') // Blocked by a piece
			{
				throw PieceInDst();
				return false;
			}

			x += dx;
			y += dy;
		}

		return true; // Valid bishop move
	}

	throw illegalMovement();
	return false;
}


Pawn::Pawn(std::string color, std::string symbol) : Piece::Piece(color, symbol)
{
}

bool Pawn::canMove(int startRow, int startCol, int endRow, int endCol)
{
	if (_symbol == "P") { // White pawn
		if (startCol == endCol && startRow - endRow == 1 && _board[endCol][endRow] == '#') {
			return true; // Move one square forward if space is empty
		}
		if (startCol == endCol && startRow == 6 && endRow == 4 && _board[endCol][endRow] == '#' && _board[startCol][startRow - 1] == '#') {
			return true; // First move: can move two squares forward
		}
		if (abs(startCol - endCol) == 1 && startRow - endRow == 1 && _board[endCol][endRow] != '#' && _board[endCol][endRow] != 'P') {
			return true; // Capture diagonally
		}
		throw illegalMovement();
	}
	// Similar logic for black pawn (piece == "p")
	else if (_symbol == "p") { // Black pawn
		if (startCol == endCol && startRow - endRow == 1 && _board[endCol][endRow] == '#') {
			return true; // Move one square forward if space is empty
		}
		if (startCol == endCol && startRow == 1 && endRow == 3 && _board[endCol][endRow] == '#' && _board[startCol][startRow - 1] == '#') {
			return true; // First move: can move two squares forward
		}
		if (abs(startCol - endCol) == 1 && startRow - endRow == 1 && _board[endCol][endRow] != '#' && _board[endCol][endRow] != 'P') {
			return true; // Capture diagonally
		}
		throw illegalMovement();
	}

	return false;
}

Knight::Knight(std::string color, std::string symbol) : Piece::Piece(color, symbol)
{
}

bool Knight::canMove(int startRow, int startCol, int endRow, int endCol)
{
	int dx = abs(endCol - startCol);
	int dy = abs(endRow - startRow);
	if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2))
	{
		return true; // Valid move for a knight
	}
	throw illegalMovement();
	return false;
}

Rook::Rook(std::string color, std::string symbol) : Piece::Piece(color, symbol)
{
}

bool Rook::canMove(int startRow, int startCol, int endRow, int endCol)
{
	if (startCol == endCol) // Moving vertically
	{
		int step = (endRow > startRow) ? 1 : -1;
		for (int i = startRow + step; i != endRow; i += step)
		{
			if (_board[startCol][i] != '#') // Blocked by a piece
			{
				throw illegalMovement();
				return false;
			}
		}
		return true;
	}
	if (startRow == endRow) // Moving horizontally
	{
		int step = (endCol > startCol) ? 1 : -1;
		for (int i = startCol + step; i != endCol; i += step)
		{
			if (_board[i][startRow] != '#') // Blocked by a piece
			{
				throw PieceInDst();
				return false;
			}
		}
		return true;
	}
	throw illegalMovement();
	return false;
}

Bishop::Bishop(std::string color, std::string symbol) : Piece::Piece(color, symbol)
{
}

bool Bishop::canMove(int startRow, int startCol, int endRow, int endCol)
{
	if (abs(endCol - startCol) == abs(endRow - startRow)) // Diagonal move
	{
		int dx = (endCol > startCol) ? 1 : -1;
		int dy = (endRow > startRow) ? 1 : -1;
		int x = startCol + dx;
		int y = startRow + dy;

		while (x != endCol && y != endRow)
		{
			if (_board[x][y] != '#') // Blocked by a piece
			{
				return false;
			}

			x += dx;
			y += dy;
		}

		return true; // Valid bishop move
	}
	throw illegalMovement();
	return false; // Invalid bishop move
}