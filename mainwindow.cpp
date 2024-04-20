#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(QString::fromUtf8("../chess/images/icon.png")));

    //ui->widget = new Game(ui->centralwidget);
    //ui->widget->setObjectName("widget");
    //ui->widget->setGeometry(QRect(110, 50, 800, 800));
    //ui->widget->update();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startGameButton_clicked()
{
    qDebug() << "Button event called!";

    ui->widget->Start();
    ui->widget->update();
    ui->startGameButton->show();
    show();

}

void MainWindow::on_saveGameButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save Game", QString(), "Game Files (*.game)");
    if (!filePath.isEmpty())
    {

        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly))
        {
            QDataStream out(&file);
            ui->widget->serialize(out);  // Serialize the game data, including ui->widget->moves
            file.close();
            qDebug() << "Game saved to:" << filePath;
        }
        else
        {
            qDebug() << "Error: Could not open file for writing";
        }
    }
}

void MainWindow::on_loadGameButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Load Game", QString(), "Game Files (*.game)");
    if (!filePath.isEmpty())
    {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly))
        {
            ui->widget->Start();

            QDataStream in(&file);
            QString moves;
            in >> moves;
            file.close();
            std::string movesStdString = moves.toStdString();
            ui->widget->setMoves(movesStdString);
            qDebug() << "Game loaded from:" << filePath;
        }
        else
        {
            qDebug() << "Error: Could not open file for reading";
        }
        ui->widget->applyMoves(ui->widget->getMoves());
    }
}





void MainWindow::on_possibleMovesButton_clicked()
{
    ui->widget->setShowPossibleMoves(!ui->widget->getShowPossibleMoves());
    ui->widget->update();
}

void MainWindow::on_radioButton_clicked()
{
    ;
}
