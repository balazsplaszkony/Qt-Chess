#include "knight.h"

Knight::Knight(File x, Rank y, Color c)
{
    square = Square(x,y);
    color = c;
    type = KNIGHT;
    firstMove = true;

    QString url;
    if (color == WHITE)
    {
        url = R"(../chess/images/wknight.png)";

    }
    else if (color == BLACK)
    {
        url = R"(../chess/images/bknight.png)";

    }    QPixmap img(url);
    pieceimage = img;
}

std::vector<Square> Knight::tracePath(Board board, std::vector<std::shared_ptr<Piece>>* Piecesptr, std::vector<Square>* Squares)
{
    *Squares = std::vector<Square>();
    File currX = getCoordinates().x;
    Rank currY = getCoordinates().y;


    // Possible sets of moves.
    int X[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int Y[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    for (int i = 0; i < 8; i++)
    {
        File newX = (File)(currX + X[i]);
        Rank newY = (Rank)(currY + Y[i]);

        if ((newX >= A && newX <= H) && (newY >= R1 && newY <= R8) &&
            (board.getBoard()[newX][newY].getPieceColor() != getColor()))
        {
            Square square(newX, newY);
            Squares->push_back(square);
        }
    }
    return possibleSquares;
}

PieceType Knight::getType() const
{
    return KNIGHT;
}

