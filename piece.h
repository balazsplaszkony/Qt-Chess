#ifndef PIECE_H
#define PIECE_H

#include <QObject>
#include <QPixmap>
#include <QPainter>

#include "board.h"

#include <vector>
#include "common.h"

class Piece  : public QObject
{
private:

protected:

public:
    Color color;
    Square square;
    bool firstMove;
    PieceType type;
    QPixmap pieceimage;
    std::vector<Square> possibleSquares;

    //static Position* gameState;

    Piece();
    Piece(File x, Rank y, Color c, PieceType t);
    virtual std::vector<Square> tracePath(Board board, std::vector<std::shared_ptr<Piece>>* Piecesptr, std::vector<Square>* Squares) = 0;
    virtual PieceType getType() const = 0;
    virtual ~Piece() {}
    virtual void move(const Square* Destination, Board* board, std::vector<std::shared_ptr<Piece>>* pieces);
    void testmove(const Square* Destination, Board* board, std::vector<std::shared_ptr<Piece>>* pieces);

    void changeImage();

    Color getColor() const;
    void setColor(Color color);
    Square getSquare();
    bool getFirstMove() const;
    void setFirstMove(bool val);

    void setCoordinates(Point point);
    Point getCoordinates() const;
    std::vector<Square> getAdjacentSquares();
    void addLegalMove(Square legalSquares);

};

#endif // PIECE_H
