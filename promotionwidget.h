#ifndef PROMOTIONWIDGET_H
#define PROMOTIONWIDGET_H

#include <QDialog>
#include <QMouseEvent>

// Assuming PieceType is an enum defined in your code
#include "piece.h"

class PromotionWidget : public QDialog
{
    Q_OBJECT

public:
    PromotionWidget(QWidget* parent = nullptr);

    // Function to retrieve the selected piece type
    PieceType getSelectedPieceType() const;

protected:
    // Override mouse press event to handle selection
    void mousePressEvent(QMouseEvent* e) override;

    // Override paint event to draw the widget
    void paintEvent(QPaintEvent* e) override;

private:
    // Private member to store the selected piece type
    PieceType type;

    // Helper function to determine the selected piece based on the mouse event
    void handleMouseSelection(const QMouseEvent* e);
};

#endif // PROMOTIONWIDGET_HPP
