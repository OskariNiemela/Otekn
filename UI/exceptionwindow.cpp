#include "exceptionwindow.hh"
namespace Student
{

exceptionWindow::exceptionWindow(std::string errorMsg) :
    _errorMsg(new QLabel()), _ok(new QPushButton())
{
    initializeWindow(errorMsg);

}

void exceptionWindow::accept()
{
    QDialog::accept();
}

void exceptionWindow::initializeWindow(std::string errorMsg)
{
    QString errorMsgQ = QString::fromStdString(errorMsg);
    _errorMsg->setText(errorMsgQ);
    QString ok = "ok";
    _ok->setText(ok);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(_errorMsg);
    layout->addWidget(_ok);
    connect(_ok,&QPushButton::clicked,this,&exceptionWindow::accept);
    QWidget* widget = new QWidget(this);
    widget->setLayout(layout);
    widget->show();
}

}



