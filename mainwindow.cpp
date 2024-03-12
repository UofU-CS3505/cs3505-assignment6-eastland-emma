#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <random>

MainWindow::MainWindow( QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Set up the input strings for the simon cpu and the user
    simonsSeq = "";
    usersSeq="";

    usersSeqIndex=0;
    //Set up timer to trigger the simon light up effect
    timer = new QTimer(this);
    connect(timer,
            &QTimer::timeout,
            this,
            &MainWindow::scheduledLightCallback);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::playSequence()
{

    std::cout<<"New Sequence: "<<simonsSeq<<std::endl;
    ui->redButton->setEnabled(false);
    ui->blueButton->setEnabled(false);
    simonsSeqIndex = 0;
    timer->start(1000);

}

void MainWindow::scheduledLightCallback()
{
    ui->redButton->setStyleSheet( QString("QPushButton::!enabled {background-color: rgb(119,119,119);} QPushButton{border:none;background-color:rgb(119, 119, 119);border-radius:85px;}} QPushButton:enabled{border:none; background-color:rgb(255, 0, 0); border-radius:85px;} QPushButton:pressed {border-radius:70px; background-color:rgb(119, 119, 119);}"));
    ui->blueButton->setStyleSheet( QString("QPushButton::!enabled {background-color: rgb(119,119,119);} QPushButton{border:none;background-color:rgb(119, 119, 119);border-radius:85px;}} QPushButton:enabled{border:none; background-color:rgb(0, 0, 255); border-radius:85px;} QPushButton:pressed {border-radius:70px; background-color:rgb(119, 119, 119);}"));
    if(simonsSeqIndex >= simonsSeq.length())
    {
        timer->stop();

        ui->redButton->setEnabled(true);
        ui->blueButton->setEnabled(true);
        return;
    }
    if(simonsSeq[simonsSeqIndex]=='0')
    {
        //light redButton
        ui->redButton->setStyleSheet( QString("QPushButton::!enabled {background-color: rgb(255,0,0);} QPushButton{border:none;background-color:rgb(255, 119, 119);border-radius:85px;}} QPushButton:enabled{border:none; background-color:rgb(255, 0, 0); border-radius:85px;} QPushButton:pressed {border-radius:70px; background-color:rgb(255, 119, 119);}"));
        ui->blueButton->setStyleSheet( QString("QPushButton::!enabled {background-color: rgb(119,119,255);} QPushButton{border:none;background-color:rgb(119, 119, 255);border-radius:85px;}} QPushButton:enabled{border:none; background-color:rgb(0, 0, 255); border-radius:85px;} QPushButton:pressed {border-radius:70px; background-color:rgb(119, 119, 255);}"));
    }
    else
    {
        //light blue button
        ui->redButton->setStyleSheet( QString("QPushButton::!enabled {background-color: rgb(255,119,119);} QPushButton{border:none;background-color:rgb(255, 119, 119);border-radius:85px;}} QPushButton:enabled{border:none; background-color:rgb(255, 0, 0); border-radius:85px;} QPushButton:pressed {border-radius:70px; background-color:rgb(255, 119, 119);}"));
        ui->blueButton->setStyleSheet( QString("QPushButton::!enabled {background-color: rgb(0,0,255);} QPushButton{border:none;background-color:rgb(119, 119, 255);border-radius:85px;}} QPushButton:enabled{border:none; background-color:rgb(0, 0, 255); border-radius:85px;} QPushButton:pressed {border-radius:70px; background-color:rgb(119, 119, 255);}"));
    }
    simonsSeqIndex++;
}

// //Adds a 1 or 0 at the end of the string (pattern) as the player is advancing through
void MainWindow::add_to_pattern()
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> distribution(0, 1);
    int random_number = distribution(rng);
    std::string newRandomGeneratedChar = std::to_string(random_number);
    simonsSeq += newRandomGeneratedChar;
}
