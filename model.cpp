#include "model.h"
#include "qtimer.h"
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
    timer = new QTimer(this);

}

Model::~Model()
{
    delete ui;
}

void Model::start_sequence()
{
    std::cout<<"New Sequence: "<<simonsSeq<<std::endl;
    ui->redButton->setEnabled(false);
    ui->blueButton->setEnabled(false);
    simonsSeqIndex = 0;
    timer->start(1000);
    for(char c :simonsSeq)
    {
        if(simonsSeqIndex >= simonsSeq.length())
        {
            emit finish_display_sequence();
        }
        if(c =='1')
        {
            emit turn_blueLight();
        }
        if(c== '0')
        {
            emit turn_redLight();
        }
    }
}
void Model::handle_redButton_signal()
{
    //event handler for pressing the red button
    std::cout<<"red button pressed"<<std::endl;
}

void Model::handle_blueButton_signal()
{
    //event handler for pressing the blue button
    std::cout<<"blue button pressed"<<std::endl;
}

void Model::handle_startButton_signal()
{
    //event handler for pressing the start button
    std::cout<<"start button pressed"<<std::endl;
    add_to_pattern();
}
void Model::handle_testseqButton_signal()
{
    std::cout<<"test seq button pressed"<<std::endl;

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


