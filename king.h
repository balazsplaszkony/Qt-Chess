#ifndef KING_H
#define KING_H

#include "piece.h"


class King : public Piece
{
private:

public:
    King(File x, Rank y, Color c);
    std::vector<Square> tracePath(Board board, std::vector<std::shared_ptr<Piece>>* Piecesptr, std::vector<Square>* Squares);
    virtual void move(const Square* Destination, Board* board, std::vector<std::shared_ptr<Piece>>* pieces);
    void testmove(const Square* Destination, Board* board, std::vector<std::shared_ptr<Piece>>* pieces);
    void handleCastling(bool kingside, Board* board, std::vector<std::shared_ptr<Piece>>* pieces);

    bool canCastleKingside(Board& board, const std::vector<std::shared_ptr<Piece>>* pieces) const;
    bool canCastleQueenside(Board& board, const std::vector<std::shared_ptr<Piece>>* pieces) const;
    bool rookHasMoved(CastlingSide side, const std::vector<std::shared_ptr<Piece>>* pieces) const;
    bool areSquaresUnderAttack(const std::vector<Square>& squares, const std::vector<std::shared_ptr<Piece>>* pieces, const Board& board) const;
    PieceType getType() const;

};

#endif // KING_H
