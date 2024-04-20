#include "piece.h"

Piece::Piece()
{
    ;
}
Piece::Piece(File x, Rank y, Color c, PieceType t)
{
    square = Square(x,y);
    color = c;
    type = t;
    firstMove = true;

}
void Piece::move(const Square* Destination, Board* board, std::vector<std::shared_ptr<Piece>>* pieces)
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

    // Update the board to indicate the piece is in the new position
    board->getBoard()[newX][newY].setPieceColor(color);
    board->getBoard()[newX][newY].setPieceType(this->type);

    // Update the coordinates of the piece
    setCoordinates(Point{newX, newY});

    // Check for a captured piece at the new position
    auto pieceToRemove = std::remove_if(pieces->begin(), pieces->end(),
                                        [newX, newY, this](const auto& piece) {
                                            return piece->getCoordinates().x == newX &&
                                                   piece->getCoordinates().y == newY &&
                                                   piece->getColor() != color;
                                        });

    // Erase the removed piece
    pieces->erase(pieceToRemove, pieces->end());

}

void Piece::testmove(const Square* Destination, Board* board, std::vector<std::shared_ptr<Piece>>* pieces)
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

    // Update the board to indicate the piece is in the new position
    board->getBoard()[newX][newY].setPieceColor(color);
    board->getBoard()[newX][newY].setPieceType(this->type);

    // Update the coordinates of the piece
    setCoordinates(Point{newX, newY});

    // Check for a captured piece at the new position
    auto pieceToRemove = std::remove_if(pieces->begin(), pieces->end(),
                                        [newX, newY, this](const auto& piece) {
                                            return piece->getCoordinates().x == newX &&
                                                   piece->getCoordinates().y == newY &&
                                                   piece->getColor() != color;
                                        });

    // Erase the removed piece
    pieces->erase(pieceToRemove, pieces->end());

    // Additional logic specific to the Piece class, if needed
    //firstMove = false;
}


Color Piece::getColor() const
{
    return color;
}
void Piece:: setColor(Color color)
{
    //this->color = color
}
Square Piece::getSquare()
{
    return square ;
}

bool Piece::getFirstMove() const
{
    return firstMove ;
}

void Piece::setFirstMove(bool val)
{
    firstMove = val;
}


void Piece::setCoordinates(Point point)
{
    square.setCoordinates(point);
}


Point  Piece:: getCoordinates() const
{
    return square.getCoordinates();
}

std::vector<Square> Piece::getAdjacentSquares()
{
    std::vector<Square> result;

    File x = square.getCoordinates().x;
    Rank y = square.getCoordinates().y;

    if (x + 1 < numberOfFiles)
    {
        result.push_back(Square((File)(x + 1), y));
        if (y + 1 < numberOfRanks)
            result.push_back(Square((File)(x + 1), (Rank)(y + 1)));
        if (y - 1 > 0)
            result.push_back(Square((File)(x + 1), (Rank)(y - 1)));
    }
    if (x - 1 > 0)
    {
        result.push_back(Square((File)(x - 1), y));
        if (y + 1 < numberOfRanks)
            result.push_back(Square((File)(x - 1), (Rank)(y + 1)));
        if (y - 1 > 0)
            result.push_back(Square((File)(x - 1), (Rank)(y - 1)));
    }
    if (y + 1 < numberOfRanks)
        result.push_back(Square(x, (Rank)(y + 1)));
    if (y - 1 > 0)
        result.push_back(Square(x, (Rank)(y - 1)));

    return result;
}

void Piece::addLegalMove(Square legalSquares)
{
    possibleSquares.push_back(legalSquares) ;
}


