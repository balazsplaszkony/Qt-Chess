#include "pawn.h"

Pawn::Pawn(File x, Rank y, Color c)
{
    square = Square(x,y);
    color = c;
    type = PAWN;
    firstMove = true;

    QString url;
    if (color == WHITE)
    {

        url = R"(../chess/images/wpawn.png)";
    }
    else if (color == BLACK)
    {
        url = R"(../chess/images/bpawn.png)";
    }

    QPixmap img(url);
    pieceimage = img;
}

std::vector<Square> Pawn::tracePath(Board board, std::vector<std::shared_ptr<Piece>>* Piecesptr, std::vector<Square>* Squares)
{
    *Squares = std::vector<Square>();
    File currX = getCoordinates().x;
    Rank currY = getCoordinates().y;

    int moveForward;

    if (color == WHITE)
        moveForward = 1;
    if (color == BLACK)
        moveForward = -1;

    // Check if the square in front is free
    if (board.getBoard()[currX][currY + moveForward].getPieceColor() == NONE)
    {
        Square freesquare(currX, (Rank)(currY + moveForward));
        Squares->push_back(freesquare);

        // Check if it's the first move and the two squares in front are free
        if (board.getBoard()[currX][currY + 2 * moveForward].getPieceColor() == NONE && firstMove)
        {
            Square freesquare(currX, (Rank)(currY + 2 * moveForward));
            Squares->push_back(freesquare);
        }
    }

    // Check for capturing diagonally to the left
    if (currX - 1 >= A && board.getBoard()[currX - 1][currY + moveForward].getPieceColor() != getColor() &&
        board.getBoard()[currX - 1][currY + moveForward].getPieceColor() != NONE)
    {
        Square enemySquare((File)(currX - 1), (Rank)(currY + moveForward));
        Squares->push_back(enemySquare);
    }

    // Check for capturing diagonally to the right
    if (currX + 1 <= H && board.getBoard()[currX + 1][currY + moveForward].getPieceColor() != getColor() &&
        board.getBoard()[currX + 1][currY + moveForward].getPieceColor() != NONE)
    {
        Square enemySquare((File)(currX + 1), (Rank)(currY + moveForward));
        Squares->push_back(enemySquare);
    }

    return possibleSquares;
}


PieceType Pawn::getType() const
{
    return PAWN;
}
