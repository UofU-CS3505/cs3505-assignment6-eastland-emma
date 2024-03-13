#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <random>

MainWindow::MainWindow(QWidget *parent)
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
    count = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    ui->blueButton->setEnabled(true);
    ui->redButton->setEnabled(true);
    ui->startButton->setEnabled(false);
    add_to_pattern();
    playSequence();
}

void MainWindow::on_redButton_clicked()
{
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
            //remove the users' pattern so far
            usersSeq="";
            usersSeqIndex =0;
            //Call the simon Pattern Display
            playSequence();
            ui->testSeqLabel->setText("UsersSeq: ");
            return;
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

void MainWindow::on_blueButton_clicked()
{
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

void MainWindow::playSequence()
{

    std::cout<<"New Sequence: "<<simonsSeq<<std::endl;
    ui->redButton->setEnabled(false);
    ui->blueButton->setEnabled(false);
    simonsSeqIndex = 0;
    timer->start(500);

}

void MainWindow::scheduledLightCallback()
{
    if(count%2==0)
    {
        ui->redButton->setStyleSheet( QString("QPushButton::!enabled {background-color: rgb(255,119,119);} QPushButton{border:none;background-color:rgb(119, 119, 119);border-radius:85px;} QPushButton:enabled{border:none; background-color:rgb(255, 0, 0); border-radius:85px;} QPushButton:pressed {border-radius:70px; background-color:rgb(119, 119, 119);}"));
        ui->blueButton->setStyleSheet( QString("QPushButton::!enabled {background-color: rgb(119,119,255);} QPushButton{border:none;background-color:rgb(119, 119, 119);border-radius:85px;} QPushButton:enabled{border:none; background-color:rgb(0, 0, 255); border-radius:85px;} QPushButton:pressed {border-radius:70px; background-color:rgb(119, 119, 119);}"));
        count++;
        return;
    }
    if(simonsSeqIndex >= simonsSeq.length())
    {
        timer->stop();

        ui->redButton->setEnabled(true);
        ui->blueButton->setEnabled(true);
        return;
        count =0;
    }
    if(simonsSeq[simonsSeqIndex]=='0')
    {
        //light redButton
        ui->redButton->setStyleSheet( QString("QPushButton::!enabled {background-color: rgb(255,0,0);} QPushButton{border:none;background-color:rgb(255, 119, 119);border-radius:85px;} QPushButton:enabled{border:none; background-color:rgb(255, 0, 0); border-radius:85px;} QPushButton:pressed {border-radius:70px; background-color:rgb(255, 119, 119);}"));
        ui->blueButton->setStyleSheet( QString("QPushButton::!enabled {background-color: rgb(119,119,255);} QPushButton{border:none;background-color:rgb(119, 119, 255);border-radius:85px;} QPushButton:enabled{border:none; background-color:rgb(0, 0, 255); border-radius:85px;} QPushButton:pressed {border-radius:70px; background-color:rgb(119, 119, 255);}"));
    }
    else
    {
        //light blue button
        ui->redButton->setStyleSheet( QString("QPushButton::!enabled {background-color: rgb(255,119,119);} QPushButton{border:none;background-color:rgb(255, 119, 119);border-radius:85px;} QPushButton:enabled{border:none; background-color:rgb(255, 0, 0); border-radius:85px;} QPushButton:pressed {border-radius:70px; background-color:rgb(255, 119, 119);}"));
        ui->blueButton->setStyleSheet( QString("QPushButton::!enabled {background-color: rgb(0,0,255);} QPushButton{border:none;background-color:rgb(119, 119, 255);border-radius:85px;} QPushButton:enabled{border:none; background-color:rgb(0, 0, 255); border-radius:85px;} QPushButton:pressed {border-radius:70px; background-color:rgb(119, 119, 255);}"));
    }
    count++;
    simonsSeqIndex++;
}

void MainWindow::add_to_pattern()
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> distribution(0, 1);
    int random_number = distribution(rng);
    std::string newRandomGeneratedChar = std::to_string(random_number);
    simonsSeq += newRandomGeneratedChar;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //Support for Arrow Keys
    if(event->key() == Qt::Key_Right)
    {
        on_blueButton_clicked();
    }
    if(event->key() == Qt::Key_Left)
    {
        on_redButton_clicked();
    }

    //Support for WASD
    if(event->key() == Qt::Key_A)
    {
        on_redButton_clicked();
    }
    if(event->key() == Qt::Key_D)
    {
        on_blueButton_clicked();
    }
}
