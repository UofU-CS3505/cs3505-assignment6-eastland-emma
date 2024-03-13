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
    emit on_startButton_clicked_signal();
}


void MainWindow::on_redButton_clicked()
{
    emit on_redButton_clicked_signal();
    std::cout<<"signal sent for red button"<<std::endl;

}

void MainWindow::on_blueButton_clicked()
{
    emit on_blueButton_clicked_signal();
    std::cout<<"signal sent for blue button"<<std::endl;
}

void MainWindow::on_seqTestButton_clicked()
{
    emit on_seqTestButton_clicked_signal();
    std::cout<<"signal sent for seqTest button"<<std::endl;
}

void MainWindow::handler_turn_red_Lights()
{
    std::cout<<"Turning on red lights"<<std::endl;
}

void MainWindow::handler_turn_blue_Lights()
{
    std::cout<<"Turning on blue lights"<<std::endl;

}
void MainWindow::handler_lose_Screen()
{
    std::cout<<"lose screen"<<std::endl;

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
