#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QPainter>
#include <iostream>
#include <QLayout>
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedSize(635,500);
    this->setStyleSheet("background-color:#1D1A10;");
    setWindowTitle(tr("Game of Life"));

    board = new Board();

    startButton = new QPushButton(tr("&Start"));
    clearButton = new QPushButton(tr("&Clear"));
    connect(startButton, SIGNAL(clicked()), board, SLOT(start()));
    connect(clearButton , SIGNAL(clicked()), board, SLOT(clear()));

    startButton->setStyleSheet("background-color: rgba(255,255,255, 0.2)");
    clearButton->setStyleSheet("background-color: rgba(255,255,255, 0.2)");

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(board, 0, 0, 0, 2);
    layout->addWidget(startButton, 1, 0);
    layout->addWidget(clearButton, 1, 1);
    setLayout(layout);
}

MainWindow::~MainWindow()
{
}

