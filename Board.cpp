#include "Board.h"
#include "Exceptions.h"
#include <iostream>
#include <cctype>

Board::Board()
{
    const char intiaboard[8][8] = {
   {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},  // Black pieces
   {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
   {'#', '#', '#', '#', '#', '#', '#', '#'},
   {'#', '#', '#', '#', '#', '#', '#', '#'},
   {'#', '#', '#', '#', '#', '#', '#', '#'},
   {'#', '#', '#', '#', '#', '#', '#', '#'},
   {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
   {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'} }; // White pieces

    for (int i = 0; i < 8;i++)
    {
        for (int j = 0; j < 8;j++)
        {
            _board[i][j] = intiaboard[i][j];
        }

    }
    
    
}


int Board::isMoveValid(std::string start, std::string end)
{
    int startRow = 8 - (start[1] - '0');
    int startCol = start[0] - 'a';

    int endRow = 8 - (end[1] - '0');
    int endCol = end[0] - 'a';

    char piece = _board[startRow][startCol];


    //code 1 valid move + check on the enemy

    //code 2
    if (_board[startRow][startCol] == '#')
    {
        throw NoPieceInSrc();
        return 2;
    }

    //code 3
    if (_board[endRow][endCol] != '#' && _board[endRow][endCol] == _board[startRow][startCol])
    {
        throw PieceInDst();
        return 3;
    }

    //code 4 invalid move + with the following move a check could be made on the current player
    if (isKingCheck(end, std::isupper(piece) ? "White" : "Black"))
    {
        throw SelfCheck();
        return 4;
    }


    //code 5 index is invalid
    if (startRow < 0 || startRow >= 8 || startCol < 0 || startCol >= 8 || endRow < 0 || endRow >= 8 || endCol < 0 || endCol >= 8)
    {
        throw illegalIndex();
        return 5;
    }

    //code 7
    if (start == end)
    {
        throw sameDstSrc();
        return 7;
    }

    //code 6 invalid move by the player
    
    std::string color = (std::isupper(piece)) ? "White" : "Black";

    if (piece == 'K' || piece == 'k')
    {
        cur = new King(color, std::string(1, piece));
    }
    else if (piece == 'P' || piece == 'p')
    {
        cur = new Pawn(color, std::string(1, piece));
    }
    else if (piece == 'Q' || piece == 'q')
    {
        cur = new Queen(color, std::string(1, piece));
    }
    else if (piece == 'B' || piece == 'b')
    {
        cur = new Bishop(color, std::string(1, piece));
    }
    else if (piece == 'N' || piece == 'n')
    {
        cur = new Knight(color, std::string(1, piece));
    }
    else if (piece == 'R' || piece == 'r')
    {
        cur = new Rook(color, std::string(1, piece));
    }
    

    if (!cur->canMove(startRow, startCol, endRow, endCol))
    {
        delete cur;
        return 6; //  valid move
    }
     
    //simulating the move on the board
    char temp = _board[endRow][endCol];
    _board[endRow][endCol] = _board[startRow][startCol];
    _board[startRow][startCol] = '#';
    
    //checking if checkmate
    std::string opColor = std::isupper(piece) ? "Black" : "White";
    if (isCheckMate(opColor))
    {
        //undoing the move
        _board[startRow][startCol] = _board[endRow][endCol];
        _board[endRow][endCol] = temp;
        delete cur;
        return 8;
    }
    //if no checkmate
    _board[startRow][startCol] = _board[endRow][endCol];
    _board[endRow][endCol] = temp;
    delete cur;
    return 0; //valid but no checkmate
}

bool Board::isKingCheck(std::string kingPos, std::string pcolor)
{
    int kingRow = 8 - (kingPos[1] - '0');
    int kingCol = kingPos[0] - 'a';

    for (int i = 0;i < 8;i++)
    {
        for (int j = 0; j < 8;j++)
        {
            char piece = _board[i][j];
            if ((pcolor == "White" && islower(piece)) || (pcolor == "Black" && isupper(piece)))
            {
                if (isPieceAttackingKing(i, j, kingRow, kingCol, piece))
                {
                    return true;
                }
            }
        }
    }
}

bool Board::isPieceAttackingKing(int startRow, int startCol, int kingRow, int kingCol, char piece)
{
    switch (tolower(piece))
    {
    case 'r':
        return isRookAttacking(startRow, startCol, kingRow, kingCol);
    case 'n':
        return isKnightAttacking(startRow, startCol, kingRow, kingCol);
    case 'q':
        return isQueenAttacking(startRow, startCol, kingRow, kingCol);
    case 'p':
        return isPawnAttacking(startRow, startCol, kingRow, kingCol);
    case 'b':
        return isBishopAttacking(startRow, startCol, kingRow, kingCol);
    default:
        return false;
    }
}

bool Board::isRookAttacking(int startRow, int startCol, int kingRow, int kingCol)
{
    if (startRow == kingRow) //checking row
    {
        //checking if there is pieces between the way
        int step = (kingCol > startCol) ? 1 : -1;
        for (int col = startCol + step;col != kingCol; col += step)
        {
            if (_board[startRow][col])
            {
                return false;
            }
        }
        return true;
    }
    else if (startCol == kingCol)
    {
        int step = (kingRow > startRow) ? 1 : -1;
        for (int row = startRow + step; row != kingRow; row += step)
        {
            if (_board[row][startCol] != '#')
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool Board::isPawnAttacking(int startRow, int startCol, int kingRow, int kingCol)
{   
    //white move up and black move down
    if (std::isupper(_board[startRow][startCol])) // white
    {
        return (startRow - 1 == kingRow && (startCol - 1 == kingCol || startCol + 1 == kingCol));
    }
    else if(std::islower(_board[startRow][startCol])) //black
    {
        return (startRow + 1 == kingRow && (startCol - 1 == kingCol || startCol + 1 == kingCol));
    }
    return false;
}

bool Board::isBishopAttacking(int startRow, int startCol, int kingRow, int kingCol)
{
    if (abs(startRow - kingRow) == abs(startCol - kingCol))
    {
        int rowStep = (kingRow > startRow) ? 1 : -1;
        int colStep = (kingCol > startCol) ? 1 : -1;
        int row = startRow + rowStep;
        int col = startCol + colStep;

        while (row != kingRow && col != kingCol)
        {
            if (_board[row][col] != '#')
            {
                return false;
            }
            row += rowStep;
            col += colStep;
        }
        return true;
    }
    return false;
}

bool Board::isQueenAttacking(int startRow, int startCol, int kingRow, int kingCol)
{
    //queen is attacking like rook and bishop
    return isRookAttacking(startRow, startCol, kingRow, kingCol) || isBishopAttacking(startRow, startCol, kingRow, kingCol);
}

bool Board::isKnightAttacking(int startRow, int startCol, int kingRow, int kingCol)
{
    int rowDiff = abs(startRow - kingRow);
    int colDiff = abs(startCol - kingCol);

    return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
}

void Board::movePiece(std::string start, std::string end)
{
    int startRow = 8 - (start[1] - '0');
    int startCol = start[0] - 'a';

    int endRow = 8 - (end[1] - '0');
    int endCol = end[0] - 'a';

    char piece = _board[startRow][startCol];

    _board[endRow][endCol] = piece;
    _board[startRow][startCol] = '#';
    std::cout << "Moved " << piece << " from " << start << " to " << end;

}



bool Board::isCheckMate(std::string color)
{
    int kingRow = -1, kingCol = -1;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8;j++)
        {
            char piece = _board[i][j];
            if ((color == "White" && piece == 'K') || (color == "Black" && piece == 'k'))
            {
                kingRow = i;
                kingCol = j;
                break;
            }
        }
    }
    //checking if the king can escacpe the check
    for (int i = kingRow - 1; i <= kingRow + 1; i++)
    {
        for (int j = kingCol - 1; j < kingCol + 1; j++)
        {
            if (i >= 0 && i < 8 && j >= 0 && j < 8)
            {
                // Check if the square is not under attack and is empty or contains a piece of the same color
                if (_board[i][j] == '#' || (std::isupper(_board[i][j]) && color == "White") || (std::islower(_board[i][j]) && color == "Black"))
                {
                    //temporaly moving the king to check if its still in check
                    char temp = _board[i][j];
                    _board[i][j] = _board[kingRow][kingCol];
                    _board[kingRow][kingCol] = '#';

                    if (!isKingCheck(std::string(1, 'a' + j) + std::to_string(8 - i), color))
                    {
                        //undoing
                        _board[kingRow][kingCol] = _board[i][j];
                        _board[i][j] = temp;
                        return false; // the king can escape so no checkmate!
                    }
                    //undoing
                    _board[kingRow][kingCol] = _board[i][j];
                    _board[i][j] = temp;
                }
            }
        }
    }
    return true;
}
