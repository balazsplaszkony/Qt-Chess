#include "king.h"

King::King(File x, Rank y, Color c)
{
    square = Square(x,y);
    color = c;
    type = KING;
    firstMove = true;

    QString url;
    if (color == WHITE)
    {
        url = R"(../chess/images/wking.png)";
    }
    else if (color == BLACK)
    {
        url = R"(../chess/images/bking.png)";
    }
    QPixmap img(url);
    pieceimage = img;
}


std::vector<Square> King::tracePath(Board board, std::vector<std::shared_ptr<Piece>>* Piecesptr, std::vector<Square>* Squares)
{
    *Squares = std::vector<Square>();
    File currX = getCoordinates().x;
    Rank currY = getCoordinates().y;

    int X[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int Y[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for (int i = 0; i < 8; i++)
    {
        File newX = (File) (currX + X[i]);
        Rank newY = (Rank) (currY + Y[i]);

        if ((newX >= A && newX <= H) && (newY >= R1 && newY <= R8) &&
            (board.getBoard()[newX][newY].getPieceColor() != getColor()))
        {
            Square square(newX, newY);
            Squares->push_back(square);
        }
    }

    // Check castling
    if (firstMove)
    {
        // Check kingside castling
        if (canCastleKingside(board, Piecesptr))
        {
            Square kingsideSquare(G, getColor() == WHITE ? R1 : R8);
            Squares->push_back(kingsideSquare);
        }

        // Check queenside castling
        if (canCastleQueenside(board, Piecesptr))
        {
            Square queensideSquare(C, getColor() == WHITE ? R1 : R8);
            Squares->push_back(queensideSquare);
        }
    }
    return possibleSquares;

}


void King::move(const Square* Destination, Board* board, std::vector<std::shared_ptr<Piece>>* pieces)
{
    File currX = getCoordinates().x;
    Rank currY = getCoordinates().y;

    board->getBoard()[currX][currY].setPieceColor(NONE);
    board->getBoard()[currX][currY].setPieceType(EMPTY);

    File newX = Destination->getCoordinates().x;
    Rank newY = Destination->getCoordinates().y;

    if(qAbs(newX - currX) > 1)
    {
        handleCastling((newX > currX), board, pieces);
    }

    // Updating the board.
    board->getBoard()[newX][newY].setPieceColor(color);
    board->getBoard()[newX][newY].setPieceType(this->type);

    // Updating the coordinates of the piece
    setCoordinates(Point{newX, newY});

    // Check for a captured piece at the new position
    auto pieceToRemove = std::remove_if(pieces->begin(), pieces->end(),
                                        [newX, newY, this](const auto& piece) {
                                            return piece->getCoordinates().x == newX &&
                                                   piece->getCoordinates().y == newY &&
                                                   piece->getColor() != color;
                                        });

    pieces->erase(pieceToRemove, pieces->end());
}

void King::testmove(const Square* Destination, Board* board, std::vector<std::shared_ptr<Piece>>* pieces)
{
    // Get the current position
    File currX = getCoordinates().x;
    Rank currY = getCoordinates().y;

    // Update the board to indicate the piece is no longer in the current position
    board->getBoard()[currX][currY].setPieceColor(NONE);
    board->getBoard()[currX][currY].setPieceType(EMPTY);

    // Get the new position
    File newX = Destination->getCoordinates().x;
    Rank newY = Destination->getCoordinates().y;

    if(qAbs(newX - currX) > 1)
    {
        handleCastling((newX > currX), board, pieces);
    }


    // Updating the board.
    board->getBoard()[newX][newY].setPieceColor(color);
    board->getBoard()[newX][newY].setPieceType(this->type);

    // Updating the coordinates of the piece
    setCoordinates(Point{newX, newY});

    // Check for a captured piece at the new position
    auto pieceToRemove = std::remove_if(pieces->begin(), pieces->end(),
                                        [newX, newY, this](const auto& piece) {
                                            return piece->getCoordinates().x == newX &&
                                                   piece->getCoordinates().y == newY &&
                                                   piece->getColor() != color;
                                        });

    pieces->erase(pieceToRemove, pieces->end());


}

void King::handleCastling(bool kingside, Board* board, std::vector<std::shared_ptr<Piece>>* pieces)
{
    // Define the coordinates of the rook based on castling type
    File rookStartX = kingside ? H : A;
    File rookEndX = kingside ? F : D;
    Rank rookY = getCoordinates().y;

    // Move the rook to the new position
    auto rook = std::find_if(pieces->begin(), pieces->end(), [rookStartX, rookY](const auto& piece) {
        return piece->getCoordinates().x == rookStartX && piece->getCoordinates().y == rookY && piece->getType() == ROOK;
    });

    if (rook != pieces->end()) {
        (*rook)->setCoordinates(Point{rookEndX, rookY});
    }

    // Move the rook to the new position
    board->getBoard()[rookEndX][rookY].setPieceColor(color);
    board->getBoard()[rookEndX][rookY].setPieceType(ROOK);

    // Clear the original positions of the king and rook
    board->getBoard()[getCoordinates().x][getCoordinates().y].setPieceColor(NONE);
    board->getBoard()[getCoordinates().x][getCoordinates().y].setPieceType(EMPTY);

    board->getBoard()[rookStartX][rookY].setPieceColor(NONE);
    board->getBoard()[rookStartX][rookY].setPieceType(EMPTY);
}
bool King::canCastleKingside(Board& board, const std::vector<std::shared_ptr<Piece>>* pieces) const
{
    File currX = getCoordinates().x;
    Rank currY = getCoordinates().y;

    // Check if the king and kingside rook have not moved
    if (!firstMove || rookHasMoved(KINGSIDE, pieces)) {
        return false;
    }

    // Check if there are no pieces between the king and rook
    for (int file = currX + 1; file < H; ++file) {
        if (board.getBoard()[(File)file][currY].getPieceColor() != NONE) {
            return false;
        }
    }
    return true;
}

bool King::canCastleQueenside(Board& board, const std::vector<std::shared_ptr<Piece>>* pieces) const
{
    File currX = getCoordinates().x;
    Rank currY = getCoordinates().y;
    // Check if the king and queenside rook have not moved
    if (!firstMove || rookHasMoved(QUEENSIDE, pieces)) {
        return false;
    }

    // Check if there are no pieces between the king and rook
    for (int file = currX - 1; file > A; --file) {
        if (board.getBoard()[(File)file][currY].getPieceColor() != NONE) {
            return false;
        }
    }
    return true;
}

bool King::rookHasMoved(CastlingSide side, const std::vector<std::shared_ptr<Piece>>* pieces) const
{
    File rookFile = (side == KINGSIDE) ? H : A;
    Rank rookRank = (getColor() == WHITE) ? R1 : R8;

    auto rook = std::find_if(pieces->begin(), pieces->end(), [&](const auto& piece) {
        return (piece->getCoordinates().x == Point{rookFile, rookRank}.x &&
                piece->getCoordinates().y == Point{rookFile, rookRank}.y &&
                piece->getType() == ROOK);
    });

    return (rook != pieces->end() && !(*rook)->getFirstMove());
}


PieceType King::getType() const
{
    return KING;
}
