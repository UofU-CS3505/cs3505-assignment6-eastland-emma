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
    void add_to_pattern();
    void start_sequence();
    void handle_redButton_signal();
    void handle_blueButton_signal();
    void handle_startButton_signal();
    void handle_testseqButton_signal();

signals:
    void turn_redLight();
    void turn_blueLight();
    void finish_display_sequence();

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
