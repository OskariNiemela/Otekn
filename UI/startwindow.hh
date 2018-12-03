#ifndef STARTWINDOW_HH
#define STARTWINDOW_HH


/* Oskari Niemelä 263440
 * Aki Kaipio 267041
 * Header file for the StartWindow class
 * asks for relevant info when starting the game
 */

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

namespace Student
{

class StartWindow : public QDialog
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param parent of the start window, by default 0
     */
    explicit StartWindow(QWidget *parent = 0);
signals:
    /**
     * @brief Sends the amount of players as a signal
     * @param player count
     */
    void sendValue(int count);

public slots:
    virtual void accept();
    virtual void reject();

private:
    QSpinBox *playerNumber_;
    QWidget *widget_;

    /**
     * @brief Initializes all the different things the window displays
     * @post exception guarantee: basic
     */
    void initializeWindow();
};

}
#endif // STARTWINDOW_HH
