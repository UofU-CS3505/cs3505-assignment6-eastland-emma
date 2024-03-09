#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <random>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //int next = std::rand()%2;
    //char nextChar = next + 48;//Converts the int zero to 48 or the int one to 49 for ascii usage

    //Set up the input strings for the simon cpu and the user
    //simonsSeq+=nextChar;

    simonsSeq = "0001010111";  //TESTING PURPOSES ONLY: I AM USING THIS TO TEST THE SIMON LIGHT UP FEATURE
    usersSeq="";

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

void MainWindow::on_startButton_clicked()
{
    ui->blueButton->setEnabled(true);
    ui->redButton->setEnabled(true);
    ui->startButton->setEnabled(false);
}


void MainWindow::on_redButton_clicked()
{
    //Used to test button responsiveness
    //TODO: Remove before turn in
    ui->testSeqLabel->setText(ui->testSeqLabel->text()+= '0');
    usersSeq += '0';
    usersSeqIndex++;
    //Checks if the user clicked the right button
    if(usersSeq[usersSeqIndex]==simonsSeq[usersSeqIndex])
    {
        //If the last button pressed was the end of the pattern
        if(static_cast<int>(simonsSeq.size())== usersSeqIndex)
        {//Successful run with patern
            //Add to the pattern
            simonsSeq = add_to_pattern(simonsSeq);
            //Call the simon Pattern Display
            //remove the users' pattern so far
        }
        return;
    }
    else
    {
        //Game over pop-up
        return;
    }
}


void MainWindow::on_blueButton_clicked()
{
    ui->testSeqLabel->setText(ui->testSeqLabel->text()+= '1');
    usersSeq += '1';
    usersSeqIndex++;
    //Checks if the user clicked the right button
    if(usersSeq[usersSeqIndex]==simonsSeq[usersSeqIndex])
    {
        //If the last button pressed was the end of the pattern
        if(static_cast<int>(simonsSeq.size())== usersSeqIndex)
        {//Successful run with patern
            //Add to the pattern
            simonsSeq = add_to_pattern(simonsSeq);
            //Call the simon Pattern Display
            //remove the users' pattern so far
        }
        return;
    }
    else
    {
        //Game over pop-up
        return;
    }
}


void MainWindow::playSequence()
{
    ui->redButton->setEnabled(false);
    ui->blueButton->setEnabled(false);
    simonsSeqIndex = 0;
    timer->start(500);

}

void MainWindow::scheduledLightCallback()
{

    if(simonsSeqIndex >= simonsSeq.length())
    {
        timer->stop();
        std::cout<<"finished";
        return;
    }
    std::cout<<simonsSeq[simonsSeqIndex];
    if(simonsSeq[simonsSeqIndex]=='0')
    {
        //light redButton
        ui->redLight->setEnabled(true);
        ui->redLight->setEnabled(false);
    }
    else
    {
        //light blue button
        ui->blueButton->setEnabled(true);
        ui->blueButton->setEnabled(false);
    }
    simonsSeqIndex++;
}

// //Adds a 1 or 0 at the end of the string (pattern) as the player is advancing through
std::string MainWindow::add_to_pattern(std::string currentPattern)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> distribution(0, 1);
    int random_number = distribution(rng);
    std::string newRandomGeneratedChar = std::to_string(random_number);
    currentPattern = currentPattern + newRandomGeneratedChar;
    return currentPattern;
}

void MainWindow::on_seqTestButton_clicked()
{
    playSequence();
}

