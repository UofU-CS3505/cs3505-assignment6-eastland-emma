#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QWidget>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    ///@brief adds a red indicator to the user's sequence and compares against the simon function to see if it is correct
    void on_redButton_clicked();
    ///@brief adds a blue indicator to the user's sequence and compares against the simon function to see if it is correct
    void on_blueButton_clicked();
    ///@brief starts the game logic
    void on_startButton_clicked();

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
    int count;

    //private helpers

    ///@brief temporarily disables the users buttons and plays the current simon sequence to the user in 1 second intervals
    void playSequence();

    ///@brief called by the timer object in order to light once every second
    void scheduledLightCallback();

    ///@brief adds a new character, either '1' or '0', to the existing simon's sequence
    void add_to_pattern();

protected:
    ///@brief overrides key inputs and allows the user to use either AD or<> keys to select buttons
    void keyPressEvent(QKeyEvent *event) override;
};
#endif // MAINWINDOW_H
