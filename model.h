#ifndef MODEL_H
#define MODEL_H

#include "mainwindow.h"
#include <QMainWindow>
#include <QTimer>
/* Model Header for Simmon -Assign06 CS3505
 * @author Emma Eastland and Johnny Song
 */

class Model : public QMainWindow
{
    Q_OBJECT
public:
    Model(QWidget *parent=nullptr);
    ~Model();

public slots:
    ///Adds to the simonSeq pattern contained in the model
    void add_to_pattern();
    ///Adds to the usersSeq and does error checking- will call either playsequence, allow the user to continue, or trigger end of game screen
    void handle_redButton_signal();
    ///Adds to the usersSeq and does error checking- will call either playsequence, allow the user to continue, or trigger end of game screen
    void handle_blueButton_signal();
    ///Starts game being procedures and configures the game in case the user had played previously
    void handle_startButton_signal();



signals:
    ///Notifies the view to light the red button
    void turn_redLight_signal();
    ///Notifies the view to light blue button
    void turn_blueLight_signal();
    ///Notifies the view to display the lose screen
    void lose_screen_signal();
    ///Notifies the view to display both buttons as off
    void turn_offLight_signal();
    ///Notifies the view to exit the lighting portion of the play sequence
    void exitLights_signal();
    ///Notifies the view to enable the play buttons & disable the start btn
    void enable_buttons_signal();
    ///Notifies the view to enable the start button & disable the play btns
    void disable_buttons_signal();
    void reset_for_keys();
    void update_progress_signal(int newProg);

private:
    Ui::MainWindow *ui;

    //Holds the current index of the simon sequence. Used in the play sequence and scheduled light callback methods
    int simonsSeqIndex;
    //Holds the index we are comparing on the user's sequence
    int usersSeqIndex;

    //Holds a count. Needed for the timer to send lighting signals correctly
    int count;

    //Holds the correct simon sequence
    std::string simonsSeq;
    //Holds the user's simon sequence
    std::string usersSeq;
    //Controls time for the simon light function
    QTimer* timer;
    //triggered by timer. sendds appropriate signals to the view
    void scheduledLightCallback();
    //Begins the timer and allows the view to display the sequence
    void playSequence();
};

#endif // MODEL_H
