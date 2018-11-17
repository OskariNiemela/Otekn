#ifndef STARTWINDOW_HH
#define STARTWINDOW_HH

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

namespace Student
{

namespace Ui {
    class startWindow;
}

class startWindow : public QDialog
{
    Q_OBJECT
public:
    explicit startWindow(QWidget *parent = 0);
signals:
    void sendValue(int count);

public slots:
    void accept();
    void reject();

private:
    Ui::startWindow *ui;
    QSpinBox* _playerNumber;
    QWidget* _widget;
};
}
#endif // STARTWINDOW_HH
