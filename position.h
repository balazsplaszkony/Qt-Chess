#ifndef POSITION_H
#define POSITION_H

#include "common.h"

#include "board.h"
#include "piece.h"
#include "pawn.h"
#include "king.h"
#include "knight.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"


#include <vector>
#include <memory>

#include <array>


class Position
{
private:
    Board chessBoard;
    int   count;    // Used for checking for 3-fold repetition rule.
    int movesSinceCaptureOrPawnPush;
    std::vector<std::shared_ptr<Piece>> pieces;
    Color playerToMove;
    int moveNumber;

public:
    bool whiteHasLegalMoves;
    bool blackHasLegalMoves;
    CheckStatus status;

    Position();

    Position(Board chessBoard);
    Position(Board chessBoard, int count);
    Board getChessBoard() ;
    void  setChessBoard(Board b);
    void  setPieces(std::vector<std::shared_ptr<Piece>> p);

    int   getCount() const;
    int   getMoveNum() const;

    Color getPlayerToMove() const;
    void updatePlayerToMove();
    int   getMovesSinceCaptureOrPawnPush() const;
    const std::vector<std::shared_ptr<Piece>> getPieces() const;

    void setPlayerToMove(Color player);
    void setMovesSinceCaptureOrPawnPush(int num);
    void setMoveNum(int num);

    void  setCount(int n);
    bool isDraw();

    void calculateLegalMoves();
    std::vector<Square> filterMoves(std::shared_ptr<Piece> tempPiece, const std::vector<Square>& possibleSquares);

    bool isSideInCheck(Color side, const Board& board, const std::vector<std::shared_ptr<Piece>>& pieces);
    CheckStatus isCheck();
    CheckStatus isCheckMate();
    bool checkForPromotion();

};

#endif // POSITION_H
