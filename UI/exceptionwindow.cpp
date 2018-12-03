/* Oskari Niemelä 263440
 * Aki Kaipio 267041
 *
 * Implementation of the exceptionwindow class
 */

#include "exceptionwindow.hh"
namespace Student
{

ExceptionWindow::ExceptionWindow(std::string errorMsg) :
    errorMsg_(new QLabel()), ok_(new QPushButton()),widget_(new QWidget(this))
{
    initializeWindow(errorMsg);

}

ExceptionWindow::~ExceptionWindow()
{
    delete widget_;
}



void ExceptionWindow::initializeWindow(std::string errorMsg)
{
    QString errorMsgQ = QString::fromStdString(errorMsg);
    errorMsg_->setText(errorMsgQ);
    QString ok = "ok";
    ok_->setText(ok);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(errorMsg_);
    layout->addWidget(ok_);
    connect(ok_,&QPushButton::clicked,this,&ExceptionWindow::reject);
    widget_->setLayout(layout);
    widget_->show();
}

}



