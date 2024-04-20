#ifndef GAME_H
#define GAME_H

#include "qwidget.h"
#include <QMouseEvent>
#include "square.h"
#include "piece.h"

#include "position.h"
#include "promotionwidget.h"

#include "common.h"

#include <vector>
#include <array>
class Square;




class Game : public QWidget
{

private:

    Board chessBoard;
    std::vector<Position> positions;
    Position currentPosition;
    Result gameStatus;
    bool pieceSelected;
    bool sameColorSelected;
    std::shared_ptr<Piece> selectedPiece;
    std::vector<Square> possibleSquares;
    PieceType promotionPieceType;
    QPixmap chessboardImage;
    bool showPossibleMoves;
    std::string moves = "";




public:

    Game();
    explicit Game(QWidget *parent = nullptr);


    void Start();
    void mousePressEvent(QMouseEvent* e) override;
    void paintEvent(QPaintEvent* e) override;
    void makeMove(File bx, Rank by);
    void selectPiece(File bx, Rank by);

    //bool checkForEnP
    void showGameOverMessageBox();

    std::shared_ptr<Piece> findPiece(int x, int y) ;

    bool getShowPossibleMoves() const;
    void setShowPossibleMoves(bool value);

    void triggerPromotion(std::vector<std::shared_ptr<Piece>>* piecesCopyptr, Board* boardCopyptr);
    void Promote();

    //std::vector<Square> filterMoves(std::shared_ptr<Piece> tempPiece, const std::vector<Square>& possibleSquares, Position& currentPosition);
    bool isPathBlocked(const Point& start, const Point& end,  Board& board);
    void addMove(const Square& start, const Square& end);
    void serialize(QDataStream& stream) ;

    void applyMoves(const std::string& move);
    bool makeMoveFromFormattedString(const std::string& move);
    std::string getMoves();
    void setMoves(std::string m);
    void SaveGame();
    void LoadGame();
    void UpdateGameStatus();

};

#endif // GAME_H
