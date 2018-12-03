/* Oskari Niemelä 263440
 * Aki Kaipio 267041
 *
 * Implementation of the StartWindow class
 */

#include "startwindow.hh"

namespace Student
{
StartWindow::StartWindow(QWidget *parent):
    QDialog(parent),playerNumber_(new QSpinBox())
{
    initializeWindow();
}

void StartWindow::accept()
{
    QDialog::accept();
    emit sendValue(playerNumber_->value());
}

void StartWindow::reject()
{
    QDialog::reject();

    emit rejected();
}

void StartWindow::initializeWindow()
{
    QGridLayout* layout = new QGridLayout(this);

    playerNumber_->setMinimum(1);
    playerNumber_->setMaximum(4);

    QLabel* playerLabel = new QLabel();
    playerLabel->setText("Number of players: ");

    QPushButton* confirm = new QPushButton();
    confirm->setText("Confirm");

    layout->addWidget(playerLabel);
    layout->addWidget(playerNumber_);
    layout->addWidget(confirm);

    widget_ = new QWidget(this);
    widget_->setLayout(layout);
    widget_->show();

    connect(confirm, &QPushButton::clicked, this, &StartWindow::accept);
}

}


