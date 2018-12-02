#ifndef EXCEPTIONWINDOW_HH
#define EXCEPTIONWINDOW_HH

#include <QDialog>
#include <QLabel>
#include <string>
#include <QPushButton>
#include <QVBoxLayout>

namespace Student
{

class ExceptionWindow : public QDialog
{
    Q_OBJECT
public:
    explicit ExceptionWindow(std::string errorMsg);
    virtual ~ExceptionWindow();

private:
    /**
     * @brief initializeWindow: Creates and shows a popup window when
     * there was an error with JSON-file
     * @param errorMsg: message to show for the user
     */
    void initializeWindow(std::string errorMsg);

    QLabel* errorMsg_;
    QPushButton* ok_;
    QWidget* widget_;
};

}


#endif // EXCEPTIONWINDOW_HH
