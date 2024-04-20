#include "promotionwidget.h"
#include <QPainter>

PromotionWidget::PromotionWidget(QWidget* parent) : QDialog(parent), type(QUEEN)
{
    setFixedSize(400, 100);
}

PieceType PromotionWidget::getSelectedPieceType() const
{
    return type;
}

void PromotionWidget::mousePressEvent(QMouseEvent* e)
{
    handleMouseSelection(e);
}

void PromotionWidget::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);

    QString url = R"(../chess/images/wqueen.png)";
    QPixmap pieceimage = QPixmap(url);
    painter.drawPixmap(QRect(0, 0, 100, 100), pieceimage);

    url = R"(../chess/images/wrook.png)";
    pieceimage = QPixmap(url);
    painter.drawPixmap(QRect(100, 0, 100, 100), pieceimage);

    url = R"(../chess/images/wbishop.png)";
    pieceimage = QPixmap(url);
    painter.drawPixmap(QRect(200, 0, 100, 100), pieceimage);

    url = R"(../chess/images/wknight.png)";
    pieceimage = QPixmap(url);
    painter.drawPixmap(QRect(300, 0, 100, 100), pieceimage);
}

void PromotionWidget::handleMouseSelection(const QMouseEvent* e)
{
    QRect rect = QRect(0, 0, 400, 100);

    int w = rect.width();
    int bw = w / 4;

    int x = e->pos().x();

    int bx = x / bw;

    switch (bx)
    {
    case 0:
        type = QUEEN;
        break;
    case 1:
        type = ROOK;
        break;
    case 2:
        type = BISHOP;
        break;
    case 3:
        type = KNIGHT;
        break;
    default:
        break;
    }


    accept(); // Close the dialog and return QDialog::Accepted
}
