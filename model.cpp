#include "model.h"
#include "ui_mainwindow.h"
#include <random>
/* Model for Simmon -Assign06 CS3505
 * @author Emma Eastland and Johnny Song
 */

Model::Model(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Set up the input strings for the simon cpu and the user
    simonsSeq = "";
    usersSeq="";
    usersSeqIndex=0;
    timer = new QTimer(this);
    connect(timer,
            &QTimer::timeout,
            this,
            &Model::scheduledLightCallback);

}
void Model::playSequence()
{
    //Disable buttons so the user can't modify the sequence
    emit disable_buttons_signal();

    simonsSeqIndex = 0;
    //Start timer to get the callback running
    timer->start(500);
}

Model::~Model()
{
    delete ui;
}

void Model::handle_redButton_signal()
{
    //add to the user sequence
    usersSeq += '0';

    //Checks if the user clicked the correct button
    if(simonsSeq.at(usersSeqIndex)== usersSeq.at(usersSeqIndex))
    {
        //If the last button pressed was the end of the pattern
        if(static_cast<int>(simonsSeq.size())== usersSeqIndex+1)
        {//Successful run with pattern
            //Add to the pattern
            add_to_pattern();

            //remove the users' pattern so far
            usersSeq="";
            usersSeqIndex =0;

            //Call the simon Pattern Display
            playSequence();
            return;
        }
        emit reset_for_keys();
        usersSeqIndex++;
        return;
    }
    else//User entered the wrong sequence
    {
        simonsSeq="";
        usersSeq="";
        usersSeqIndex = 0;
        simonsSeqIndex = 0;
        emit reset_for_keys();
        //Game over pop-up
        emit lose_screen_signal();
        return;
    }
}

void Model::handle_blueButton_signal()
{
    usersSeq += '1';

    //Checks if the user clicked the correct button
    if(simonsSeq.at(usersSeqIndex) == usersSeq.at(usersSeqIndex))
    {

        //If the last button pressed was the end of the pattern
        if(static_cast<int>(simonsSeq.size())== usersSeqIndex+1)
        {//Successful run with pattern
            //Add to the pattern
            add_to_pattern();

            //remove the users' pattern so far
            usersSeq="";
            usersSeqIndex =0;
            //Call the simon Pattern Display
            playSequence();
            return;
        }
        emit reset_for_keys();
        usersSeqIndex++;
        return;
    }
    else//Pattern was wrong
    {
        simonsSeq="";
        usersSeq="";
        usersSeqIndex = 0;
        simonsSeqIndex = 0;
        //Game over pop-up
        emit reset_for_keys();
        emit lose_screen_signal();
        return;
    }
}

void Model::handle_startButton_signal()
{
    //Get the first item in the sequence
    add_to_pattern();
    //Display to user
    playSequence();
}

void Model::add_to_pattern()
{
    //Select a number randomly
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> distribution(0, 1);
    int random_number = distribution(rng);

    //Convert to string for easy reading
    std::string newRandomGeneratedChar = std::to_string(random_number);

    //Add to the sequence
    simonsSeq += newRandomGeneratedChar;
}

void Model::scheduledLightCallback()
{
    //Decide if this is an on cycle(display new light) or and off cycle(turn off both lights)
    if(count%2==0)//Off cycle
    {
        emit turn_offLight_signal();//changes both lights to inactive
        count++;
        return;
    }

    if(simonsSeqIndex >= static_cast<int>(simonsSeq.length()))//Finished iteration
    {
        timer->stop();
        emit exitLights_signal();//enables the buttons so the user can play again
        count =0;
        return;
    }

    if(simonsSeq[simonsSeqIndex]=='0')//On cycle- Red
    {
        //light redButton
        emit turn_redLight_signal();
    }
    else//On cycle- Blue
    {
        //light blue button
        emit turn_blueLight_signal();
    }
    count++;
    simonsSeqIndex++;
}
