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
    std::cout<<"Signal for play sequence emmited"<<std::endl;
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
    std::cout<<"red button pressed"<<std::endl;
    //Used to test button responsiveness
    //TODO: Remove before turn in
    ui->testSeqLabel->setText(ui->testSeqLabel->text()+= '0');
    usersSeq += '0';
    std::cout<<"Your Sequence: "<<usersSeq<<"\t"<<"correct Sequence: "<<simonsSeq<<std::endl;
    //Checks if the user clicked the right button
    if(simonsSeq.at(usersSeqIndex)== usersSeq.at(usersSeqIndex))
    {
        std::cout<<simonsSeq.size()<<"    "<<usersSeqIndex+1<<std::endl;
        //If the last button pressed was the end of the pattern
        if(static_cast<int>(simonsSeq.size())== usersSeqIndex+1)
        {//Successful run with patern
            //Add to the pattern
            add_to_pattern();
            std::cout<<"New pattern added"<<std::endl;
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
    std::cout<<"blue button pressed"<<std::endl;
    ui->testSeqLabel->setText(ui->testSeqLabel->text()+= '1');
    usersSeq += '1';
    std::cout<<"Your Sequence: "<<usersSeq<<"\t"<<"correct Sequence: "<<simonsSeq<<std::endl;
    //Checks if the user clicked the right button
    if(simonsSeq.at(usersSeqIndex) == usersSeq.at(usersSeqIndex))
    {
        std::cout<<simonsSeq.size()<<"    "<<usersSeqIndex+1<<std::endl;
        //If the last button pressed was the end of the pattern
        if(static_cast<int>(simonsSeq.size())== usersSeqIndex+1)
        {//Successful run with patern
            //Add to the pattern
            add_to_pattern();
            std::cout<<"New pattern added"<<std::endl;
            //remove the users' pattern so far
            usersSeq="";
            usersSeqIndex =0;
            //Call the simon Pattern Display
            playSequence();
            std::cout<<"Signal for play sequence emmited"<<std::endl;
            //increase score
            ui->testSeqLabel->setText("UsersSeq: ");
            return;
        }

        usersSeqIndex++;
        return;
    }
    else
    {
        std::cout<<"lose screen model"<<std::endl;
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
    simonsSeq = "";
    add_to_pattern();
    playSequence();
    emit enable_buttons_signal();
    std::cout<<"Added to pattern"<<std::endl;

}

void Model::handle_testseqButton_signal()
{
    std::cout<<"test seq button pressed"<<std::endl;

}

void Model::add_to_pattern()
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> distribution(0, 1);
    int random_number = distribution(rng);
    std::string newRandomGeneratedChar = std::to_string(random_number);
    simonsSeq += newRandomGeneratedChar;
    std::cout<<"Pattern added!"<<std::endl;
    std::cout<<simonsSeq<<std::endl;


}

void Model::scheduledLightCallback()
{
    if(count%2==0)
    {
        emit turn_offLight_signal();//changes both lights to inactive
        count++;
        return;
    }
    if(simonsSeqIndex >= simonsSeq.length())
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
