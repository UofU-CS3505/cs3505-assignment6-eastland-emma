#include "model.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <random>

Model::Model(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Set up the input strings for the simon cpu and the user
    simonsSeq = "";
    usersSeq="";
    usersSeqIndex=0;
    connect(ui->startButton,
            &QAbstractButton::clicked,
            this,
            &Model::on_startButton_clicked);

    connect(ui->blueButton,
            &QAbstractButton::clicked,
            this,
            &Model::on_blueButton_clicked);

    connect(ui->redButton,
            &QAbstractButton::clicked,
            this,
            &Model::on_redButton_clicked);

    connect(ui->seqTestButton,
            &QAbstractButton::clicked,
            this,
            &Model::on_seqTestButton_clicked);
}

Model::~Model()
{
    delete ui;
}

void Model::on_startButton_clicked()
{
    ui->blueButton->setEnabled(true);
    ui->redButton->setEnabled(true);
    ui->startButton->setEnabled(false);
    add_to_pattern();
    emit on_startButton_clicked();
}


void Model::on_redButton_clicked()
{
    //Used to test button responsiveness
    //TODO: Remove before turn in
    ui->testSeqLabel->setText(ui->testSeqLabel->text()+= '0');
    usersSeq += '0';
    std::cout<<"Your Sequence: "<<usersSeq<<"\t"<<"correct Sequence: "<<simonsSeq<<std::endl;
    //Checks if the user clicked the right button
    if(simonsSeq.at(usersSeqIndex)=='0')
    {
        std::cout<<simonsSeq.size()<<"    "<<usersSeqIndex+1<<std::endl;
        //If the last button pressed was the end of the pattern
        if(static_cast<int>(simonsSeq.size())== usersSeqIndex+1)
        {//Successful run with patern
            //Add to the pattern
            add_to_pattern();
            //remove the users' pattern so far
            usersSeq="";
            usersSeqIndex =0;
            //Call the simon Pattern Display
            emit on_redButton_clicked_signal();
        }

        usersSeqIndex++;
        return;
    }
    else
    {
        ui->blueButton->setEnabled(false);
        ui->redButton->setEnabled(false);
        ui->startButton->setEnabled(true);
        simonsSeq="";
        usersSeq="";
        usersSeqIndex = 0;
        simonsSeqIndex = 0;
        //Game over pop-up
        return;
    }
}


void Model::on_blueButton_clicked()
{
    ui->testSeqLabel->setText(ui->testSeqLabel->text()+= '1');
    usersSeq += '1';
    std::cout<<"Your Sequence: "<<usersSeq<<"\t"<<"correct Sequence: "<<simonsSeq<<std::endl;
    //Checks if the user clicked the right button
    if(simonsSeq.at(usersSeqIndex) == '1')
    {
        std::cout<<simonsSeq.size()<<"    "<<usersSeqIndex+1<<std::endl;
        //If the last button pressed was the end of the pattern
        if(static_cast<int>(simonsSeq.size())== usersSeqIndex+1)
        {//Successful run with patern
            //Add to the pattern
            add_to_pattern();
            //remove the users' pattern so far
            usersSeq="";
            usersSeqIndex =0;
            //Call the simon Pattern Display
            emit on_blueButton_clicked_signal();
            //increase score
        }

        usersSeqIndex++;
        return;
    }
    else
    {
        ui->blueButton->setEnabled(false);
        ui->redButton->setEnabled(false);
        ui->startButton->setEnabled(true);
        simonsSeq ="";
        usersSeq = "";
        usersSeqIndex = 0;
        simonsSeqIndex = 0;
        //Game over pop-up
        return;
    }
}

// //Adds a 1 or 0 at the end of the string (pattern) as the player is advancing through
void Model::add_to_pattern()
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> distribution(0, 1);
    int random_number = distribution(rng);
    std::string newRandomGeneratedChar = std::to_string(random_number);
    simonsSeq += newRandomGeneratedChar;
}

void Model::on_seqTestButton_clicked()
{
    emit on_seqTestButton_clicked_signal();
}
