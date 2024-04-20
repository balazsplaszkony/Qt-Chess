#include "bishop.h"

Bishop::Bishop(File x, Rank y, Color c)
{
    square = Square(x,y);
    color = c;
    type = BISHOP;
    firstMove = true;


    QString url;
    if (color == WHITE)
    {
        url = R"(../chess/images/wbishop.png)";
    }
    else if (color == BLACK)
    {
        url = R"(../chess/images/bbishop.png)";
    }
    QPixmap img(url);
    pieceimage = img;
}

std::vector<Square> Bishop::tracePath(Board board, std::vector<std::shared_ptr<Piece>>* Piecesptr, std::vector<Square>* Squares)
{
    *Squares = std::vector<Square>();
    int currX = getCoordinates().x;
    int currY = getCoordinates().y;

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
PieceType Bishop::getType() const
{
    return BISHOP;
}
