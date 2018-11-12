#include "startwindow.hh"

startWindow::startWindow(QWidget *parent):
    QDialog(parent),_playerNumber(new QSpinBox())
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

    QWidget* widget = new QWidget(this);
    widget->setLayout(layout);
    widget->show();

    connect(confirm, &QPushButton::clicked, this, &startWindow::accept);
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
