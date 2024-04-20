#include "position.h"


Position::Position()
{
    chessBoard = Board();
    count = 1;    // Used for checking for 3-fold repetition rule.
    moveNumber = 0;
    movesSinceCaptureOrPawnPush = 0;
    pieces.push_back(std::make_unique<Pawn>(A, R2, WHITE));
    pieces.push_back(std::make_unique<Pawn>(B, R2, WHITE));
    pieces.push_back(std::make_unique<Pawn>(C, R2, WHITE));
    pieces.push_back(std::make_unique<Pawn>(D, R2, WHITE));
    pieces.push_back(std::make_unique<Pawn>(E, R2, WHITE));
    pieces.push_back(std::make_unique<Pawn>(F, R2, WHITE));
    pieces.push_back(std::make_unique<Pawn>(G, R2, WHITE));
    pieces.push_back(std::make_unique<Pawn>(H, R2, WHITE));
    pieces.push_back(std::make_unique<Rook>(A, R1, WHITE));
    pieces.push_back(std::make_unique<Knight>(B, R1, WHITE));
    pieces.push_back(std::make_unique<Bishop>(C, R1, WHITE));
    pieces.push_back(std::make_unique<Queen>(D, R1, WHITE));
    pieces.push_back(std::make_unique<King>(E, R1, WHITE));
    pieces.push_back(std::make_unique<Bishop>(F, R1, WHITE));
    pieces.push_back(std::make_unique<Knight>(G, R1, WHITE));
    pieces.push_back(std::make_unique<Rook>(H, R1, WHITE));

    pieces.push_back(std::make_unique<Pawn>(A, R7, BLACK));
    pieces.push_back(std::make_unique<Pawn>(B, R7, BLACK));
    pieces.push_back(std::make_unique<Pawn>(C, R7, BLACK));
    pieces.push_back(std::make_unique<Pawn>(D, R7, BLACK));
    pieces.push_back(std::make_unique<Pawn>(E, R7, BLACK));
    pieces.push_back(std::make_unique<Pawn>(F, R7, BLACK));
    pieces.push_back(std::make_unique<Pawn>(G, R7, BLACK));
    pieces.push_back(std::make_unique<Pawn>(H, R7, BLACK));
    pieces.push_back(std::make_unique<Rook>(A, R8, BLACK));
    pieces.push_back(std::make_unique<Knight>(B, R8, BLACK));
    pieces.push_back(std::make_unique<Bishop>(C, R8, BLACK));
    pieces.push_back(std::make_unique<Queen>(D, R8, BLACK));
    pieces.push_back(std::make_unique<King>(E, R8, BLACK));
    pieces.push_back(std::make_unique<Bishop>(F, R8, BLACK));
    pieces.push_back(std::make_unique<Knight>(G, R8, BLACK));
    pieces.push_back(std::make_unique<Rook>(H, R8, BLACK));
}



Position::Position(Board chessBoard) : chessBoard(chessBoard)
{
}


Position::Position(Board chessBoard, int count) : chessBoard(chessBoard), count(count){

}

Board Position::getChessBoard()
{
    return chessBoard;
}
void  Position::setChessBoard(Board b)
{
    chessBoard = b;
}
void  Position::setPieces(std::vector<std::shared_ptr<Piece>> p)
{
    pieces = p;
}
int   Position::getCount() const
{
    return count;
}
int   Position::getMoveNum() const
{
    return moveNumber;
}




Color Position::getPlayerToMove() const
{
    return playerToMove;
}

void Position::updatePlayerToMove()
{
    if (playerToMove == WHITE)
        playerToMove = BLACK;
    else if (playerToMove == BLACK)
        playerToMove = WHITE;
}


int   Position::getMovesSinceCaptureOrPawnPush() const
{
    return movesSinceCaptureOrPawnPush;
}

const std::vector<std::shared_ptr<Piece>>  Position::getPieces() const
{
    return pieces;
}


void Position::setPlayerToMove(Color player)
{
    playerToMove = player;
}

void Position::setMovesSinceCaptureOrPawnPush(int num)
{
    movesSinceCaptureOrPawnPush = num;
}
void Position::setMoveNum(int num)
{
    moveNumber = num;
}


void  Position::setCount(int n)
{
    count = n;
}



bool Position::isDraw()
{
    bool result = false;

    // Checking for 3-fold repetition.
    if (count == 3)
    {
        result = true;
    }

    // Checking for 50 move rule.
    else if (movesSinceCaptureOrPawnPush > 50)
    {
        result = true;
    }

    else
    {
        /* Checking for insufficient material.
        A king + any(pawn, rook, queen) is sufficient.
        A king and more than one other type of piece is sufficient (e.g. knight + bishop).
        A king and two (or more) knights is sufficient.
        King + knight against king + any(rook, bishop, knight, pawn) is sufficient.
        King + bishop against king + any(knight, pawn) is sufficient.
        Otherwise, it's insufficient mating material.
        */
        bool sufficientMaterial = false;
        if (pieces.size() >= 4)
        {
            sufficientMaterial = true;
        }
        else
        {
            // Determine the types of remaining pieces
            int hasKing = 0;
            int hasPawn = 0;
            int hasRook = 0;
            int hasBishop = 0;
            int hasKnight = 0;
            int hasQueen = 0;

            for (const auto& piece : pieces)
            {
                if (piece->getType() == KING)
                {
                    hasKing++;
                }
                else if (piece->getType() == PAWN)
                {
                    hasPawn++;
                }
                else if (piece->getType() == ROOK)
                {
                    hasRook++;
                }
                else if (piece->getType() == BISHOP)
                {
                    hasBishop++;
                }
                else if (piece->getType() == KNIGHT)
                {
                    hasKnight++;
                }
                else if (piece->getType() == QUEEN)
                {
                    hasQueen++;
                }
            }

            // Check for specific combinations of remaining pieces
            if ((hasKing && (hasPawn || hasRook || hasQueen)) ||
                (hasKing && hasKnight && hasBishop) ||
                (hasKing && hasKnight > 1) ||
                (hasKing && hasBishop > 1))
            {
                sufficientMaterial = true;
            }
        }
        if (sufficientMaterial == false)
        {
            result = true;
        }

        const std::vector<std::shared_ptr<Piece>>& currentPieces = getPieces();
        std::vector<std::shared_ptr<Piece>> piecesCopy = currentPieces;
        // Checking for stalemate.
        if (sufficientMaterial)
        {
            // Stalemate occurs if the player has no legal moves
            if (((!whiteHasLegalMoves) && playerToMove == WHITE) ||
                ((!blackHasLegalMoves) && playerToMove == BLACK))
            {
                result = true;
            }
        }
    }

    return result;
}

// Calculates the legal moves for all pieces.
void Position:: calculateLegalMoves()
{
    bool whiteLegalMoves= false;
    bool blackLegalMoves= false;

    for (const auto& piece : pieces)
    {
        piece->possibleSquares = std::vector<Square>();
        // Calculate possible moves
        const std::vector<std::shared_ptr<Piece>>& currentPieces = pieces;
        std::vector<std::shared_ptr<Piece>> piecesCopy = currentPieces;
        std::vector<Square> squares = std::vector<Square>();

        //Determine possible moves for the given piece
        std::vector<Square> possibleSquares = piece->tracePath(chessBoard, &piecesCopy, &squares);

        // Filter out moves that would put the player in check.
        std::vector<Square> legalMoves = filterMoves(piece, squares);

        for (const auto& legalSquare : legalMoves)
        {
            piece->addLegalMove(legalSquare);
        }

        if (!legalMoves.empty())
        {
            if (piece->getColor() == WHITE)
                whiteLegalMoves = true;
            if (piece->getColor() == BLACK)
                blackLegalMoves = true;
        }
    }

    whiteHasLegalMoves = whiteLegalMoves;
    blackHasLegalMoves = blackLegalMoves;
}

std::vector<Square> Position::filterMoves(std::shared_ptr<Piece> tempPiece, const std::vector<Square>& possibleSquares)
{
    std::vector<Square> filteredSquares;

    File originalX = tempPiece->getSquare().getCoordinates().x;
    Point originalPosition = tempPiece->getCoordinates();

    // Simulate all possible moves by making them on the board and checking if it would put the player in check.
    for (size_t i = 0; i < possibleSquares.size(); ++i)
    {
        Position tempPosition = *this;
        const Board& tempBoard = tempPosition.getChessBoard();
        Board TempboardCopy = tempBoard;

        const std::vector<std::shared_ptr<Piece>>& currentPieces = pieces;
        std::vector<std::shared_ptr<Piece>> piecesCopy = currentPieces;

        const Square* tempSquare = &possibleSquares[i];

        // Simulate the move
        tempPiece->testmove(tempSquare, &TempboardCopy, &piecesCopy);

        tempPosition.setChessBoard(TempboardCopy);
        tempPosition.setPieces(piecesCopy);
        if ((tempPosition.isCheck() == NO_CHECK ||
            (tempPosition.isCheck() == WHITE_IN_CHECK && tempPiece->getColor() == BLACK) ||
            (tempPosition.isCheck() == BLACK_IN_CHECK && tempPiece->getColor() == WHITE)) &&

            // Filtering out castling moves made while in check
            (status != WHITE_IN_CHECK || tempPiece->getColor() != WHITE || tempPiece->getType() != KING
            || qAbs(originalX - tempPiece->getCoordinates().x) < 2) &&
            (status != BLACK_IN_CHECK || tempPiece->getColor() != BLACK || tempPiece->getType() != KING
             || qAbs(originalX - tempPiece->getCoordinates().x) < 2)
            )
        {
            filteredSquares.push_back(possibleSquares[i]);
        }

        // Reset the position to the original state
        tempPiece->setCoordinates(originalPosition);
    }

    return filteredSquares;
}


bool Position::isSideInCheck(Color side, const Board& board, const std::vector<std::shared_ptr<Piece>>& pieces)
{
    // Find the king of the specified side
    std::shared_ptr<King> king = nullptr;
    for (const auto& piece : pieces)
    {
        if (piece->getType() == KING && piece->getColor() == side)
        {
            king = std::static_pointer_cast<King>(piece);
            break;
        }
    }

    if (!king)
    {
        return false;
    }

    Point kingPosition = king->getCoordinates();
    const std::vector<std::shared_ptr<Piece>>& currentPieces = getPieces();
    std::vector<std::shared_ptr<Piece>> piecesCopy = currentPieces;

    // Check if any opposing piece can attack the king.
    for (const auto& piece : pieces)
    {
        if (piece->getColor() != side)
        {
            std::vector<Square> squares = std::vector<Square>();
            std::vector<Square> attackSquares = piece->tracePath(board, &piecesCopy, &squares);
            for (const auto& square : squares)
            {
                if (square.getCoordinates().x == kingPosition.x && square.getCoordinates().y == kingPosition.y)
                {
                    // The king is in check.
                    return true;
                }
            }
        }
    }
    return false;
}
CheckStatus Position::isCheck()
{
    CheckStatus retval = NO_CHECK;

    if (isSideInCheck(WHITE, chessBoard, pieces) &&
        isSideInCheck(BLACK, chessBoard, pieces))
    {
        retval = BOTH_IN_CHECK;
    }
    else if (isSideInCheck(WHITE, chessBoard, pieces))
    {
        retval = WHITE_IN_CHECK;
    }
    else if (isSideInCheck(BLACK, chessBoard, pieces))
    {
        retval = BLACK_IN_CHECK;
    }
    return retval;
}

CheckStatus Position::isCheckMate()
{
    CheckStatus checkStatus = isCheck();
    // If player is in check and has no legal moves game is over.
    if (checkStatus == WHITE_IN_CHECK && (!whiteHasLegalMoves) && playerToMove == WHITE)
    {
        return WHITE_CHECKMATED;
    }
    if (checkStatus == BLACK_IN_CHECK && (!blackHasLegalMoves) && playerToMove == BLACK)
    {
        return BLACK_CHECKMATED;
    }
    else
    {
        return NO_CHECK;
    }
}
