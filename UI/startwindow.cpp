#include "startwindow.hh"

startWindow::startWindow(QWidget *parent):
    QDialog(parent)
{
    QGridLayout* layout = new QGridLayout(this);

    QSpinBox* playerNumber = new QSpinBox();
    playerNumber->setMinimum(1);
    playerNumber->setMaximum(4);

    QLabel* playerLabel = new QLabel();
    playerLabel->setText("Number of players: ");

    QPushButton* confirm = new QPushButton();
    confirm->setText("Confirm");

    layout->addWidget(playerLabel);
    layout->addWidget(playerNumber);
    layout->addWidget(confirm);

    QWidget* widget = new QWidget(this);
    widget->setLayout(layout);
    widget->show();

    connect(confirm, &QPushButton::clicked, this, &startWindow::accept);
}

void startWindow::accept()
{
    QDialog::accept();

    emit accepted();

}

void startWindow::reject()
{
    QDialog::reject();

    emit rejected();
}
