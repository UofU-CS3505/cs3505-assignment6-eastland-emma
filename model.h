#ifndef MODEL_H
#define MODEL_H

#include "ui_mainwindow.h"
#include <QMainWindow>

class Model : public QMainWindow
{
    Q_OBJECT
public:
    Model(QWidget *parent=nullptr);
    ~Model();

public slots:
    //handler for adding pattern
    void add_to_pattern();
    //handler for pressing the red button signal
    void handle_redButton_signal();
    //handler for pressing the blue button signal
    void handle_blueButton_signal();
    //handler for pressing the start button signal
    void handle_startButton_signal();

signals:
    //signal for turning the red light
    void turn_redLight_signal();
    //signal for turning the blue light
    void turn_blueLight_signal();
    //signal that indicates when the sequence has finished
    void finish_display_sequence_signal();
    //signal for when the player loses
    void lose_screen_signal();
    //signal for playing the sequence that the player has to follow
    void playSequence_signal();

private:
    //UI for modifying the ui file
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
};

#endif // MODEL_H
