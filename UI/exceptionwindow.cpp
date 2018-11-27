#include "exceptionwindow.hh"
namespace Student
{

exceptionWindow::exceptionWindow(std::string errorMsg) :
    _errorMsg(new QLabel()), _ok(new QPushButton()),_widget(new QWidget(this))
{
    initializeWindow(errorMsg);

}

exceptionWindow::~exceptionWindow()
{
    delete _widget;
}

void exceptionWindow::reject()
{
    QDialog::reject();
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
    connect(_ok,&QPushButton::clicked,this,&exceptionWindow::reject);
    _widget->setLayout(layout);
    _widget->show();
}

}



