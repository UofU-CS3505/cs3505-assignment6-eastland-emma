
#include "model.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <random>
#include <QTimer>


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
    emit disable_buttons_signal();
    simonsSeqIndex = 0;
    timer->start(500);
}

Model::~Model()
{
    delete ui;
}

void Model::handle_redButton_signal()
{
    //event handler for pressing the red button
    //Used to test button responsiveness
    //TODO: Remove before turn in
    ui->testSeqLabel->setText(ui->testSeqLabel->text()+= '0');
    usersSeq += '0';
    //Checks if the user clicked the right button
    if(simonsSeq.at(usersSeqIndex)== usersSeq.at(usersSeqIndex))
    {
        //If the last button pressed was the end of the pattern
        if(static_cast<int>(simonsSeq.size())== usersSeqIndex+1)
        {//Successful run with patern
            //Add to the pattern
            add_to_pattern();
            //remove the users' pattern so far
            usersSeq="";
            usersSeqIndex =0;
            //Call the simon Pattern Display
            playSequence();
            //std::cout<<"Signal for play sequence emmited"<<std::endl;
            ui->testSeqLabel->setText("UsersSeq: ");
            return;
        }

        usersSeqIndex++;
        return;
    }
    else
    {
        simonsSeq="";
        usersSeq="";
        usersSeqIndex = 0;
        simonsSeqIndex = 0;
        //Game over pop-up
        emit lose_screen_signal();
        return;
    }
}

void Model::handle_blueButton_signal()
{
    //event handler for pressing the blue button
    ui->testSeqLabel->setText(ui->testSeqLabel->text()+= '1');
    usersSeq += '1';
    //Checks if the user clicked the right button
    if(simonsSeq.at(usersSeqIndex) == usersSeq.at(usersSeqIndex))
    {
        //If the last button pressed was the end of the pattern
        if(static_cast<int>(simonsSeq.size())== usersSeqIndex+1)
        {//Successful run with patern
            //Add to the pattern
            add_to_pattern();
            //remove the users' pattern so far
            usersSeq="";
            usersSeqIndex =0;
            //Call the simon Pattern Display
            playSequence();
            //increase score
            ui->testSeqLabel->setText("UsersSeq: ");
            return;
        }

        usersSeqIndex++;
        return;
    }
    else
    {
        simonsSeq="";
        usersSeq="";
        usersSeqIndex = 0;
        simonsSeqIndex = 0;
        //Game over pop-up
        emit lose_screen_signal();
        return;
    }
}

void Model::handle_startButton_signal()
{
    //simonsSeq = "";
    add_to_pattern();
    std::cout<<simonsSeq<<std::endl;
    playSequence();
   // emit enable_buttons_signal();
}


void Model::add_to_pattern()
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> distribution(0, 1);
    int random_number = distribution(rng);
    std::string newRandomGeneratedChar = std::to_string(random_number);
    simonsSeq += newRandomGeneratedChar;
}

void Model::scheduledLightCallback()
{
    if(count%2==0)
    {
        emit turn_offLight_signal();//changes both lights to inactive
        count++;
        return;
    }
    if(simonsSeqIndex >= static_cast<int>(simonsSeq.length()))
    {
        timer->stop();
        emit exitLights_signal();//enables the buttons so the user can play again
        count =0;
        return;
    }
    if(simonsSeq[simonsSeqIndex]=='0')
    {
        //light redButton
        emit turn_redLight_signal();
    }
    else
    {
        //light blue button
        emit turn_blueLight_signal();
    }
    count++;
    simonsSeqIndex++;
}
