#ifndef MODEL_H
#define MODEL_H

#include "ui_mainwindow.h"
#include <QMainWindow>

class Model : public QMainWindow
{
    Q_OBJECT
public:
    explicit Model(QMainWindow *parent=nullptr);
    Model(QWidget *parent = nullptr);

    ~Model();

public slots:
    //private helpers

    ///@brief adds a red indicator to the user's sequence and compares against the simon function to see if it is correct
    void on_redButton_clicked();
    ///@brief adds a blue indicator to the user's sequence and compares against the simon function to see if it is correct
    void on_blueButton_clicked();
    ///@brief starts the game logic
    void on_startButton_clicked();
    ///REMOVE BEFORE TURN IN
    void on_seqTestButton_clicked();
    ///@brief adds a new character, either '1' or '0', to the existing simon's sequence
    void add_to_pattern();
signals:

    void on_redButton_clicked_signal();
    void on_blueButton_clicked_signal();
    void on_seqTestButton_clicked_signal();

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


};

#endif // MODEL_H
