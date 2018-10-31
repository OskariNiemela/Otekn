#include "mainwindow.hh"

Mainwindow::Mainwindow(QWidget *parent)
    : QMainWindow(parent),
      _board(std::make_shared<GameBoard>()),
      _gameState(std::make_shared<GameState>()),
      _gameEngine(Logic::GameEngine(_board, _gameState, _players))
{
    QGraphicsView* gameView = _board->showScene();

    QHBoxLayout* hLayout = new QHBoxLayout(this);

    hLayout->addWidget(gameView);

    QVBoxLayout* vLayout = new QVBoxLayout(this);

    QColor colour(100,100,100);
    QPixmap colorMap(64,64);

    QLabel* label = new QLabel(this);

    colorMap.fill(colour);

    label->setPixmap(colorMap);

    vLayout->addWidget(label);


    hLayout->addLayout(vLayout);

    QWidget* widget = new QWidget();
    widget->setLayout(hLayout);
    widget->show();
}





