#include "game.h"
#include <QPainter>
#include <QDebug>
#include <QDialog>
#include <QFile>
#include <QDir>

#include <QMessageBox>

Game::Game()
{
}

Game::Game(QWidget *parent) : QWidget(parent)
{
    setGeometry(QRect(110, 50, 800, 800));

    QString url = R"(../chess/images/board.png)";
    QPixmap img(url);

    chessboardImage = img;
    showPossibleMoves = true;
    this->setVisible(true);

    this->Start();
    this->update();
    this->show();
}
void Game:: Start()
{
    currentPosition = Position();
    gameStatus = ONGOING;
    currentPosition.setMovesSinceCaptureOrPawnPush(0);
    currentPosition.setPlayerToMove(WHITE);
    pieceSelected = false;
    selectedPiece = nullptr;
    possibleSquares = std::vector<Square>();
    currentPosition.calculateLegalMoves();
    positions = std::vector<Position>();
    positions.push_back(currentPosition);
    moves = "";

}

void Game::mousePressEvent(QMouseEvent* e)
{
    if (gameStatus != ONGOING)
        return;

    QRect rect= QRect(110, 50, 800, 800);
    int w=rect.width();
    int h=rect.height();
    int bw=w/8;
    int bh=h/8;

    int y = e->pos().y();
    int x = e->pos().x();

    File bx= (File)(x/bw);
    Rank by= (Rank)(7 - y/bh);
    makeMove(bx, by);
}

void Game::paintEvent(QPaintEvent* e)
{
    Q_UNUSED(e);

    QPainter painter(this);

    // Painting board.
    painter.drawPixmap(QRect(0, 0, 800, 800), chessboardImage);

    std::vector<std::shared_ptr<Piece>> pieces = currentPosition.getPieces();

    // Painting pieces.
    for (const auto& piece : pieces)
    {
        Point coordinates = piece->getSquare().getCoordinates();
        int plusx = coordinates.x;
        int plusy = 7 - coordinates.y;
        painter.drawPixmap(QRect(0 + (plusx * 100), 0 + (plusy * 100), 100, 100), piece->pieceimage);
    }
    // Painting circles on squares that the selected piece can move to.
    if (showPossibleMoves)
    {
        for (auto it = possibleSquares.begin(); it != possibleSquares.end(); ++it)
        {
            Point coordinates = it->getCoordinates();
            int plusx = coordinates.x;
            int plusy = 7 - coordinates.y;
            painter.setBrush(Qt::red);
            painter.drawEllipse(QPointF(50 + plusx * 100, 50 + plusy * 100), 10, 10);
        }

    }
}
void Game::makeMove(File bx, Rank by)
{
    Square selectedSquare = currentPosition.getChessBoard().getBoard()[bx][by];
    const Square* selectedSquarePtr = &selectedSquare;

    sameColorSelected = false;
    if (pieceSelected == true)
    {
        std::shared_ptr<Piece> enemyPiece;
        enemyPiece = findPiece(selectedSquare.getCoordinates().x, selectedSquare.getCoordinates().y);
        if (enemyPiece != nullptr && enemyPiece->getColor() == currentPosition.getPlayerToMove())
        {
            sameColorSelected = true;
            pieceSelected = false;
            selectedPiece = nullptr;
        }
    }
    if (pieceSelected == false)
    {
        selectPiece(bx, by);
    }
    else if (pieceSelected == true)
    {
        bool pawnMove = (selectedPiece->getType() == PAWN);

        // Piece and square are selected, loop through possible moves.
        for (int i = 0; i < possibleSquares.size(); i++)
        {
            // If selected square is in the list make the move.
            if (possibleSquares[i].getCoordinates().x == bx && possibleSquares[i].getCoordinates().y == by)
            {
                int pieceCountOriginal = currentPosition.getPieces().size();
                const Board& currentBoard = currentPosition.getChessBoard();
                const std::vector<std::shared_ptr<Piece>>& currentPieces = currentPosition.getPieces();
                Board boardCopy = currentBoard;
                std::vector<std::shared_ptr<Piece>> piecesCopy = currentPieces;
                // Save coordinates to string
                addMove(selectedPiece->getSquare(), *selectedSquarePtr);
                // Make move
                selectedPiece->move(selectedSquarePtr, &boardCopy, &piecesCopy);
                selectedPiece->setFirstMove(false);

                currentPosition.setChessBoard(boardCopy);
                currentPosition.setPieces(piecesCopy);

                // Checking for promotion.
                if (selectedPiece->getType() == PAWN && (
                        (selectedPiece->getCoordinates().y == 7 && selectedPiece->getColor() == WHITE) ||
                        (selectedPiece->getCoordinates().y == 0 && selectedPiece->getColor() == BLACK)))
                {
                    triggerPromotion(&piecesCopy, &boardCopy);
                }

                possibleSquares = std::vector<Square>();
                currentPosition.setMoveNum(currentPosition.getMoveNum() + 1);

                // Updating color that makes the next move.
                currentPosition.updatePlayerToMove();

                // Applying 50 move-rule.
                int pieceCountNew = currentPosition.getPieces().size();
                currentPosition.setMovesSinceCaptureOrPawnPush(currentPosition.getMovesSinceCaptureOrPawnPush() +
                                                               ((!pawnMove) && (pieceCountNew == pieceCountOriginal)));

                // Checking for same board in earlier positions
                for (auto it = positions.begin(); it != positions.end(); ++it)
                    if (currentPosition.getChessBoard() == it->getChessBoard())
                        currentPosition.setCount(it->getCount() + 1);

                // Checking for checkmate and draw
                UpdateGameStatus();

                // Save current positon
                positions.push_back(currentPosition);
                currentPosition = positions.back();

                // If game is over show dialog window.
                if (gameStatus != ONGOING)
                    showGameOverMessageBox();
                break;
            }
        }
        update();
    }
}

void Game::selectPiece(File bx, Rank by)
{
    selectedPiece = findPiece(bx, by);
    if (selectedPiece != nullptr && selectedPiece->getColor() == currentPosition.getPlayerToMove())
    {
        if (!selectedPiece->possibleSquares.empty() ||  sameColorSelected)
        {
        possibleSquares = selectedPiece->possibleSquares;
        pieceSelected = true;
        sameColorSelected = false;
        update();
        }
    }
}


void Game::showGameOverMessageBox()
{
    QString message;

    switch (gameStatus)
    {
    case BLACK_WON:
        message = "Black won!";
        break;
    case WHITE_WON:
        message = "White won!";
        break;
    case DRAW:
        message = "Draw!";
        break;
    default: break;
    }
    QMessageBox::information(this, "Game Over", message);
}



// Show the pop-up message box

std::shared_ptr<Piece> Game::findPiece(int x, int y)
{
    const auto& pieces = currentPosition.getPieces();

    for (size_t i = 0; i < pieces.size(); ++i)
    {
        int ax = pieces[i]->getSquare().getCoordinates().x;
        int ay = pieces[i]->getSquare().getCoordinates().y;
        if (ax == x &&
            ay == y)
        {
            return pieces[i];
        }
    }
    return nullptr;
}

bool Game::getShowPossibleMoves() const
{
    return showPossibleMoves;
}

void Game::setShowPossibleMoves(bool value)
{
    showPossibleMoves = value;
}

void Game::triggerPromotion(std::vector<std::shared_ptr<Piece>>* piecesCopyptr, Board* boardCopyptr)
{
    for (auto it = piecesCopyptr->begin(); it != piecesCopyptr->end(); ++it)
    {
        const auto& piece = *it;
        if (piece->getCoordinates().x == selectedPiece->getCoordinates().x &&
            piece->getCoordinates().y == selectedPiece->getCoordinates().y &&
            piece->getColor() == selectedPiece->getColor())
        {
            piecesCopyptr->erase(it);
            possibleSquares = std::vector<Square>();
            update();
            break;
        }
    }

    PromotionWidget promotionWidget(this);

    if (promotionWidget.exec() == QDialog::Accepted)
    {
        promotionPieceType = promotionWidget.getSelectedPieceType();

    }
    switch (promotionPieceType)
    {
    case KNIGHT:
    {
        piecesCopyptr->push_back(std::make_unique<Knight>(selectedPiece->getCoordinates().x,
                                                          selectedPiece->getCoordinates().y, selectedPiece->getColor()));
        break;
    }
    case BISHOP:
    {
        piecesCopyptr->push_back(std::make_unique<Bishop>(selectedPiece->getCoordinates().x,
                                                          selectedPiece->getCoordinates().y, selectedPiece->getColor()));
        break;
    }
    case ROOK:
    {
        piecesCopyptr->push_back(std::make_unique<Rook>(selectedPiece->getCoordinates().x,
                                                        selectedPiece->getCoordinates().y, selectedPiece->getColor()));
        break;
    }
    case QUEEN:
    {
        piecesCopyptr->push_back(std::make_unique<Queen>(selectedPiece->getCoordinates().x,
                                                         selectedPiece->getCoordinates().y, selectedPiece->getColor()));
        break;
    }
    default: break;
    }
    currentPosition.setChessBoard(*boardCopyptr);
    currentPosition.setPieces(*piecesCopyptr);
}

char numericToLetter(int numericCoordinate)
{
    if (numericCoordinate < 1 || numericCoordinate > 8)
    {
        // Handle invalid input
        return '\0';
    }

    return static_cast<char>('A' + numericCoordinate );
}
int letterToNumeric(char letter) {
    if (letter < 'A' || letter > 'H') {
        // Handle invalid input
        return -1;
    }

    return letter - 'A';
}


void Game::addMove(const Square& start, const Square& end)
{
    // Format the move string and add it to the moves
    std::string move = {numericToLetter(start.getCoordinates().x), static_cast<char>(start.getCoordinates().y + 1)};
    move += ":";
    move += {numericToLetter(end.getCoordinates().x), static_cast<char>(end.getCoordinates().y + 1)};
    moves += move + ":";
}



void Game::serialize(QDataStream& stream)
{
    stream << QString::fromStdString(moves);
}

void Game::applyMoves(const std::string& moves)
{
    std::istringstream iss(moves);
    char X1, Y1, separator1, X2, Y2, separator2;

    while (iss >> X1 >> Y1 >> separator1 >> X2 >> Y2 >> separator2)
    {
        makeMove((File)letterToNumeric(X1), (Rank)(Y1 - 1));

        makeMove((File)letterToNumeric(X2), (Rank)(Y2 - 1));
    }
}

std::string Game::getMoves()
{
    return moves;
}
void Game::setMoves(std::string m)
{
    moves = m;
}


void Game::UpdateGameStatus()
{
    currentPosition.status = currentPosition.isCheck();
    currentPosition.calculateLegalMoves();
    CheckStatus status = currentPosition.isCheckMate();
    if (status == WHITE_CHECKMATED)
        gameStatus = BLACK_WON;
    else if (status == BLACK_CHECKMATED)
        gameStatus = WHITE_WON;
    else if (currentPosition.isDraw() == true)
    {
        gameStatus = DRAW;
    }
}


