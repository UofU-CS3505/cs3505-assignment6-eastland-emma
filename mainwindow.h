#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    ///@brief temporarily disables the users buttons and plays the current simon sequence to the user in 1 second intervals
    void playSequence();

    ///@brief called by the timer object in order to light once every second
    void scheduledLightCallback();

    ///@brief adds a new character, either '1' or '0', to the existing simon's sequence
    void add_to_pattern();

private:
    Ui::MainWindow *ui;

    //Holds the current index of the simon sequence. Used in the play sequence and scheduled light callback methods
    int simonsSeqIndex;
    //Holds the index we are comparing on the user's sequence
    int usersSeqIndex;

    //Holds the correct simon sequence
    std::string simonsSeq;
    //Holds the user's simon sequence
    std::string usersSeq;

    //Controls time for the simon light function
    QTimer* timer;

    //private helpers


};
#endif // MAINWINDOW_H
