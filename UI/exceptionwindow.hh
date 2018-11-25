#ifndef EXCEPTIONWINDOW_HH
#define EXCEPTIONWINDOW_HH

#include <QDialog>
#include <QLabel>
#include <string>
#include <QPushButton>
#include <QVBoxLayout>
namespace Student
{

class exceptionWindow : public QDialog
{
    Q_OBJECT
public:
    explicit exceptionWindow(std::string errorMsg);

public slots:
    void accept();
private:
    void initializeWindow(std::string errorMsg);
    QLabel* _errorMsg;
    QPushButton* _ok;
};

}


#endif // EXCEPTIONWINDOW_HH
