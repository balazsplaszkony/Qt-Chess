#include "square.h"

Square::Square()
{

}
Square::Square(File x, Rank y)
{
    coordinates.x = x;
    coordinates.y = y;
}

Color Square:: getColor() const
{
    return squareColor;
}
void Square:: setColor(Color color)
{
    squareColor = color;
}
Color Square:: getPieceColor() const
{
    return pieceColor;
}
PieceType Square:: getPieceType() const
{
    return pieceType;
}
void Square::setPieceColor(Color color)
{
    pieceColor = color;
}
void Square::setPieceType(PieceType type)
{
    pieceType = type;
}
Point Square:: getCoordinates() const
{
    return coordinates;
}
void  Square:: setCoordinates(Point point)
{
    coordinates.x = point.x;
    coordinates.y = point.y;
}

bool Square::operator==(const Square& s) const
{
    return (coordinates.x == s.coordinates.x && coordinates.y == s.coordinates.y &&
            pieceColor == s.pieceColor && pieceType == s.getPieceType() );
}
Square& Square::operator=(const Square& other)
{
    if (this != &other)
    {
        coordinates = other.coordinates;
        squareColor = other.squareColor;
        pieceColor = other.pieceColor;
        pieceType = other.pieceType;
    }
    return *this;
}
