#include "queen.h"

Queen::Queen(File x, Rank y, Color c)
{
    square = Square(x,y);
    color = c;
    type = QUEEN;
    firstMove = true;


    QString url;
    if (color == WHITE)
    {
        url = R"(../chess/images/wqueen.png)";
    }
    else if (color == BLACK)
    {
        url = R"(../chess/images/bqueen.png)";
    }
    QPixmap img(url);
    pieceimage = img;
}

std::vector<Square> Queen::tracePath(Board board, std::vector<std::shared_ptr<Piece>>* Piecesptr, std::vector<Square>* Squares)
{
    *Squares = std::vector<Square>();
    File currX = getCoordinates().x;
    Rank currY = getCoordinates().y;

    // Checking horizontal and vertical. If there is a piece stop going further.

    for (int i = currX + 1; i <= numberOfRanks; i++ )
    {
        if (board.getBoard()[i][currY].getPieceColor() == NONE)
        {
            Square freesquare((File)i, currY);
            Squares->push_back(freesquare);
        }
        else if (board.getBoard()[(File)i][currY].getPieceColor() != getColor())
        {
            Square enemysquare((File)i, currY);
            Squares->push_back(enemysquare);
            break;
        }
        else
            break;
    }
    for (int i = currX - 1; i >=  0; i-- )
    {
        if (board.getBoard()[i][currY].getPieceColor() == NONE)
        {
            Square freesquare((File)i, currY);
            Squares->push_back(freesquare);
        }
        else if (board.getBoard()[i][currY].getPieceColor() != getColor())
        {
            Square enemysquare((File)i, currY);
            Squares->push_back(enemysquare);
            break;
        }
        else
            break;
    }
    for (int i = currY + 1; i <= numberOfFiles; i++ )
    {
        if (board.getBoard()[currX][i].getPieceColor() == NONE)
        {
            Square freesquare(currX, (Rank)i);
            Squares->push_back(freesquare);
        }
        else if (board.getBoard()[currX][i].getPieceColor() != getColor())
        {
            Square enemysquare(currX, (Rank)i);
            Squares->push_back(enemysquare);
            break;
        }
        else
            break;
    }
    for (int i = currY - 1; i >=  0; i-- )
    {
        if (board.getBoard()[currX][i].getPieceColor() == NONE)
        {
            Square freesquare(currX, (Rank)i);
            Squares->push_back(freesquare);
        }
        else if (board.getBoard()[currX][i].getPieceColor() != getColor())
        {
            Square enemysquare(currX, (Rank)i);
            Squares->push_back(enemysquare);
            break;
        }
        else
            break;
    }

    // Checking all diagonals. If there is a piece stop going further.

    for (int i = currX + 1, j = currY + 1; i <= numberOfRanks && j <= numberOfFiles ; i++, j++ )
    {
        if (board.getBoard()[i][j].getPieceColor() == NONE)
        {
            Square freesquare((File)i, (Rank)j);
            Squares->push_back(freesquare);
        }
        else if (board.getBoard()[i][j].getPieceColor() != getColor())
        {
            Square enemysquare((File)i, (Rank)j);
            Squares->push_back(enemysquare);
            break;
        }
        else
            break;
    }
    for (int i = currX + 1, j = currY - 1; i <= numberOfRanks && j >= 0 ; i++, j-- )
    {
        if (board.getBoard()[i][j].getPieceColor() == NONE)
        {
            Square freesquare((File)i, (Rank)j);
            Squares->push_back(freesquare);
        }
        else if (board.getBoard()[i][j].getPieceColor() != getColor())
        {
            Square enemysquare((File)i, (Rank)j);
            Squares->push_back(enemysquare);
            break;
        }
        else
            break;
    }
    for (int i = currX - 1, j = currY + 1; i >= 0 && j <= numberOfFiles ; i--, j++ )
    {
        if (board.getBoard()[i][j].getPieceColor() == NONE)
        {
            Square freesquare((File)i, (Rank)j);
            Squares->push_back(freesquare);
        }
        else if (board.getBoard()[i][j].getPieceColor() != getColor())
        {
            Square enemysquare((File)i, (Rank)j);
            Squares->push_back(enemysquare);
            break;
        }
        else
            break;
    }
    for (int i = currX - 1, j = currY - 1; i >= 0 && j >= 0 ; i--, j-- )
    {
        if (board.getBoard()[i][j].getPieceColor() == NONE)
        {
            Square freesquare((File)i, (Rank)j);
            Squares->push_back(freesquare);
        }
        else if (board.getBoard()[i][j].getPieceColor() != getColor())
        {
            Square enemysquare((File)i, (Rank)j);
            Squares->push_back(enemysquare);
            break;
        }
        else
            break;
    }
    return possibleSquares;
}
PieceType Queen::getType() const
{
    return QUEEN;
}
