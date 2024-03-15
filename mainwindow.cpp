#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <chrono>
#include <thread>

MainWindow::MainWindow( QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    ui->testSeqLabel->setText("");
    ui->startButton->setEnabled(false);
    emit on_startButton_clicked_signal();
}


void MainWindow::on_redButton_clicked()
{
    emit on_redButton_clicked_signal();
}

void MainWindow::on_blueButton_clicked()
{
    emit on_blueButton_clicked_signal();
}

void MainWindow::handler_disable_buttons()
{
    ui->blueButton->setEnabled(false);
    ui->redButton->setEnabled(false);
}
void MainWindow::handler_enable_buttons()
{
    ui->blueButton->setEnabled(true);
    ui->redButton->setEnabled(true);
    ui->startButton->setEnabled(false);
}
void MainWindow::handler_turn_red_Lights()
{
    ui->redButton->setStyleSheet( QString("QPushButton::!enabled {background-color: rgb(255,0,0);} QPushButton{border:none;background-color:rgb(255, 119, 119);border-radius:85px;} QPushButton:enabled{border:none; background-color:rgb(255, 0, 0); border-radius:85px;} QPushButton:pressed {border-radius:70px; background-color:rgb(255, 119, 119);}"));
    ui->blueButton->setStyleSheet( QString("QPushButton::!enabled {background-color: rgb(119,119,255);} QPushButton{border:none;background-color:rgb(119, 119, 255);border-radius:85px;} QPushButton:enabled{border:none; background-color:rgb(0, 0, 255); border-radius:85px;} QPushButton:pressed {border-radius:70px; background-color:rgb(119, 119, 255);}"));
}
void MainWindow::handler_turn_blue_Lights()
{
    ui->redButton->setStyleSheet( QString("QPushButton::!enabled {background-color: rgb(255,119,119);} QPushButton{border:none;background-color:rgb(255, 119, 119);border-radius:85px;} QPushButton:enabled{border:none; background-color:rgb(255, 0, 0); border-radius:85px;} QPushButton:pressed {border-radius:70px; background-color:rgb(255, 119, 119);}"));
    ui->blueButton->setStyleSheet( QString("QPushButton::!enabled {background-color: rgb(0,0,255);} QPushButton{border:none;background-color:rgb(119, 119, 255);border-radius:85px;} QPushButton:enabled{border:none; background-color:rgb(0, 0, 255); border-radius:85px;} QPushButton:pressed {border-radius:70px; background-color:rgb(119, 119, 255);}"));
}
void MainWindow::handler_exitLights()
{
    ui->redButton->setEnabled(true);
    ui->blueButton->setEnabled(true);
}
void MainWindow::handler_turn_off_Lights()
{
    ui->redButton->setStyleSheet( QString("QPushButton::!enabled {background-color: rgb(255,119,119);} QPushButton{border:none;background-color:rgb(119, 119, 119);border-radius:85px;} QPushButton:enabled{border:none; background-color:rgb(255, 0, 0); border-radius:85px;} QPushButton:pressed {border-radius:70px; background-color:rgb(119, 119, 119);}"));
    ui->blueButton->setStyleSheet( QString("QPushButton::!enabled {background-color: rgb(119,119,255);} QPushButton{border:none;background-color:rgb(119, 119, 119);border-radius:85px;} QPushButton:enabled{border:none; background-color:rgb(0, 0, 255); border-radius:85px;} QPushButton:pressed {border-radius:70px; background-color:rgb(119, 119, 119);}"));
}
void MainWindow::handler_lose_Screen()
{
    ui->blueButton->setEnabled(false);
    ui->redButton->setEnabled(false);
    ui->startButton->setEnabled(true);
    ui->testSeqLabel->setText("Game Over- Press start to try again");
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
