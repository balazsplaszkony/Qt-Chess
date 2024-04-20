#ifndef BOARD_H
#define BOARD_H

#define NUM_OF_FILES (8U)
#define NUM_OF_RANKS (8U)
#include "common.h"

#include <vector>
#include <array>


#include "square.h"


class Board
{
private:
    std::array<std::array<Square, numberOfFiles>, numberOfRanks> board;
public:
    Board();
    void drawChessBoard();
    std::array<std::array<Square, numberOfFiles>, numberOfRanks>& getBoard();
    void setBoard(std::array<std::array<Square, numberOfFiles>, numberOfRanks> chessBoard);
    //std::array<std::array<Square, numberOfFiles>, numberOfRanks> getBoard( );
    bool operator==(const Board& b);
    //void operator=(const Board& b);


};


#endif // BOARD_H
