#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece
{
private:
public:
    Pawn(File x, Rank y, Color c);
    std::vector<Square> tracePath(Board board, std::vector<std::shared_ptr<Piece>>* Piecesptr, std::vector<Square>* Squares);
    PieceType getType() const;

};

#endif // PAWN_H
