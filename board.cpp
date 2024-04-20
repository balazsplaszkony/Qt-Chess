#include "board.h"

Board::Board()
{
    for (int i = 0; i < numberOfFiles; i++)
    {
        for (int j = 0; j < numberOfRanks; j++)
        {
            Point p;
            p.x = (File)i;
            p.y = (Rank)j;
            board[i][j].setCoordinates(p);
            if (j < 2)
            {
                board[i][j].setPieceColor(WHITE);
                if (j == 1)
                    board[i][j].setPieceType(PAWN);
                else
                {
                    if (i == 0 || i == 7)
                        board[i][j].setPieceType(ROOK);
                    if (i == 1 || i == 6)
                        board[i][j].setPieceType(KNIGHT);
                    if (i == 2 || i == 5)
                        board[i][j].setPieceType(BISHOP);
                    if (i == 3)
                        board[i][j].setPieceType(QUEEN);
                    if (i == 4)
                        board[i][j].setPieceType(KING);
                }
            }
            else if (j < 6)
            {
                board[i][j].setPieceColor(NONE);
                board[i][j].setPieceType(EMPTY);
            }
            else
            {
                board[i][j].setPieceColor(BLACK);
                if (j == 1)
                    board[i][j].setPieceType(PAWN);
                else
                {
                    if (i == 0 || i == 7)
                        board[i][j].setPieceType(ROOK);
                    if (i == 1 || i == 6)
                        board[i][j].setPieceType(KNIGHT);
                    if (i == 2 || i == 5)
                        board[i][j].setPieceType(BISHOP);
                    if (i == 3)
                        board[i][j].setPieceType(QUEEN);
                    if (i == 4)
                        board[i][j].setPieceType(KING);
                }
            }
        }
    }

}

std::array<std::array<Square, numberOfFiles>, numberOfRanks>& Board::getBoard()
{
    return   board;
}
void Board::setBoard(std::array<std::array<Square, numberOfFiles>, numberOfRanks> chessBoard)
{
    board = chessBoard;
}

bool Board::operator==(const Board& b)
{
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            if(!(board[i][j] == b.board[i][j]))
                return false;

    return true;
}
/*void Board::operator=(const Board& b)
{
    board = b.board;
}
*/
