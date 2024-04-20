#ifndef SQUARE_H
#define SQUARE_H


#include "common.h"

//#include "piece.h"




class Square
{
private:
    Point coordinates;
    Color squareColor;
    Color pieceColor;
    PieceType pieceType;

public:
    Square();
    Square(File x, Rank y);
    Color getColor() const;
    void setColor(Color color);
    Color getPieceColor() const;
    PieceType getPieceType() const;

    void setPieceColor(Color color);
    void setPieceType(PieceType color);

    Point getCoordinates() const;
    void setCoordinates(Point point);
    bool operator==(const Square& s) const;
    Square& operator=(const Square& other);


};

#endif // SQUARE_H
