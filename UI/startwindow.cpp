#include "startwindow.hh"

namespace Student
{
startWindow::startWindow(QWidget *parent):
    QDialog(parent),_playerNumber(new QSpinBox())
{
    initializeWindow();
}

void startWindow::accept()
{
    QDialog::accept();
    emit sendValue(_playerNumber->value());
}

void startWindow::reject()
{
    QDialog::reject();

    emit rejected();
}

void startWindow::initializeWindow()
{
    QGridLayout* layout = new QGridLayout(this);

    _playerNumber->setMinimum(1);
    _playerNumber->setMaximum(4);

    QLabel* playerLabel = new QLabel();
    playerLabel->setText("Number of players: ");

    QPushButton* confirm = new QPushButton();
    confirm->setText("Confirm");

    layout->addWidget(playerLabel);
    layout->addWidget(_playerNumber);
    layout->addWidget(confirm);

    _widget = new QWidget(this);
    _widget->setLayout(layout);
    _widget->show();

    connect(confirm, &QPushButton::clicked, this, &startWindow::accept);
}

}


