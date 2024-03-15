#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
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
    MainWindow( QWidget *parent = nullptr);
    ~MainWindow();
    //handler for turning red lights signal
    void handler_turn_red_Lights();
    //handler for turning blue lights signal
    void handler_turn_blue_Lights();
    //handler for losing screen
    void handler_lose_Screen();

public slots:
    ///REMOVE BEFORE TURN IN
    void on_seqTestButton_clicked();
    ///@brief called by the timer object in order to light once every second
    void scheduledLightCallback();
    //handler for playing the sequence that the player has to follow
    void playSequence();

signals:
    //signal for pressing the red button
    void on_redButton_clicked_signal();
    //signal for pressing the blue button
    void on_blueButton_clicked_signal();

    void on_seqTestButton_clicked_signal();
    //signal for pressing the start button
    void on_startButton_clicked_signal();

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

protected:
    ///@brief overrides key inputs and allows the user to use either AD or<> keys to select buttons
    void keyPressEvent(QKeyEvent *event) override;
};
#endif // MAINWINDOW_H
