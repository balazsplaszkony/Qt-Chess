#ifndef COMMON_H
#define COMMON_H

#include <QDebug>
#include <QtMath>
#include <QString>
#include <sstream>
#include <sstream>


constexpr  int numberOfFiles = 8;
constexpr  int numberOfRanks = 8;

typedef enum
{
    NONE = 0,
    WHITE,
    BLACK
} Color;


typedef enum
{
    EMPTY = 0,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
} PieceType;

typedef enum
{
    NORMAL = 0,
    CASTLE,
    EN_PASSANT,
    PROMOTION
} MoveType;


typedef enum
{
    ONGOING = 0,
    WHITE_WON,
    BLACK_WON,
    DRAW
} Result;

typedef enum
{
    NO_CHECK = 0,
    WHITE_IN_CHECK,
    BLACK_IN_CHECK,
    BOTH_IN_CHECK,
    WHITE_CHECKMATED,
    BLACK_CHECKMATED
} CheckStatus;
typedef enum   {
    KINGSIDE,
    QUEENSIDE
}CastlingSide;

typedef enum
{
    A = 0,
    B,
    C,
    D,
    E,
    F,
    G,
    H
} File;

typedef enum
{
    R1 = 0,
    R2,
    R3,
    R4,
    R5,
    R6,
    R7,
    R8
} Rank;



typedef struct Point{
    File x;
    Rank y;
}Point;



#endif // COMMON_H
