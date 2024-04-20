#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece
{
public:
    Queen(File x, Rank y, Color c);
    std::vector<Square> tracePath(Board board, std::vector<std::shared_ptr<Piece>>* Piecesptr, std::vector<Square>* Squares);
    PieceType getType() const;

};

#endif // QUEEN_H
