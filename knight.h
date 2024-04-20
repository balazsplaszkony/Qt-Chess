#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece
{
public:
    Knight(File x, Rank y, Color c);
    std::vector<Square> tracePath(Board board, std::vector<std::shared_ptr<Piece>>* Piecesptr, std::vector<Square>* Squares);
    PieceType getType() const;
};

#endif // KNIGHT_H
