#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>

#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startGameButton_clicked();

    void on_saveGameButton_clicked();

    void on_loadGameButton_clicked();

    void on_radioButton_clicked();

    void on_possibleMovesButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
