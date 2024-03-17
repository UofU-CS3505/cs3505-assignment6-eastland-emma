#include "mainwindow.h"
#include "ui_mainwindow.h"
/* View and Controller for Simmon -Assign06 CS3505
 * @author Emma Eastland and Johnny Song
 */

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
    //Clear game over, if needed
    ui->gameOverLabel->setText("");
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
    //Disable play buttons
    ui->blueButton->setEnabled(false);
    ui->redButton->setEnabled(false);
}
void MainWindow::handler_enable_buttons()
{
    //Enable Play buttons
    ui->blueButton->setEnabled(true);
    ui->redButton->setEnabled(true);
    //Disable start buttons
    ui->startButton->setEnabled(false);
}
void MainWindow::handler_turn_red_Lights()
{
    //Light Red, Dim Blue
    ui->redButton->setStyleSheet( QString("QPushButton::!enabled {background-color: rgb(255,0,0);} QPushButton{border:none;background-color:rgb(255, 119, 119);border-radius:85px;} QPushButton:enabled{border:none; background-color:rgb(255, 0, 0); border-radius:85px;} QPushButton:pressed {border-radius:70px; background-color:rgb(255, 119, 119);}"));
    ui->blueButton->setStyleSheet( QString("QPushButton::!enabled {background-color: rgb(119,119,255);} QPushButton{border:none;background-color:rgb(119, 119, 255);border-radius:85px;} QPushButton:enabled{border:none; background-color:rgb(0, 0, 255); border-radius:85px;} QPushButton:pressed {border-radius:70px; background-color:rgb(119, 119, 255);}"));
}
void MainWindow::handler_turn_blue_Lights()
{
    //Dim Red, Light Blue
    ui->redButton->setStyleSheet( QString("QPushButton::!enabled {background-color: rgb(255,119,119);} QPushButton{border:none;background-color:rgb(255, 119, 119);border-radius:85px;} QPushButton:enabled{border:none; background-color:rgb(255, 0, 0); border-radius:85px;} QPushButton:pressed {border-radius:70px; background-color:rgb(255, 119, 119);}"));
    ui->blueButton->setStyleSheet( QString("QPushButton::!enabled {background-color: rgb(0,0,255);} QPushButton{border:none;background-color:rgb(119, 119, 255);border-radius:85px;} QPushButton:enabled{border:none; background-color:rgb(0, 0, 255); border-radius:85px;} QPushButton:pressed {border-radius:70px; background-color:rgb(119, 119, 255);}"));
}
void MainWindow::handler_exitLights()
{
    //Enable buttons
    ui->redButton->setEnabled(true);
    ui->blueButton->setEnabled(true);
}
void MainWindow::handler_turn_off_Lights()
{
    //Dim both lights
    ui->redButton->setStyleSheet( QString("QPushButton::!enabled {background-color: rgb(255,119,119);} QPushButton{border:none;background-color:rgb(119, 119, 119);border-radius:85px;} QPushButton:enabled{border:none; background-color:rgb(255, 0, 0); border-radius:85px;} QPushButton:pressed {border-radius:70px; background-color:rgb(119, 119, 119);}"));
    ui->blueButton->setStyleSheet( QString("QPushButton::!enabled {background-color: rgb(119,119,255);} QPushButton{border:none;background-color:rgb(119, 119, 119);border-radius:85px;} QPushButton:enabled{border:none; background-color:rgb(0, 0, 255); border-radius:85px;} QPushButton:pressed {border-radius:70px; background-color:rgb(119, 119, 119);}"));
}
void MainWindow::handler_lose_Screen()
{
    //Disable play buttons
    ui->blueButton->setEnabled(false);
    ui->redButton->setEnabled(false);
    //Enable start button
    ui->startButton->setEnabled(true);
    //Notify player of Game Over
    ui->gameOverLabel->setText("Game Over- Press start to try again");
}

void MainWindow::handler_update_progress(int newProg)
{
    ui->progressBar->setValue(newProg);
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //Support for Arrow Keys
    if(event->key() == Qt::Key_Right&&ui->blueButton->isEnabled())
    {
        ui->blueButton->setStyleSheet( QString("QPushButton{border:none;background-color:rgb(119, 119, 255);border-radius:75px;}"));
        on_blueButton_clicked();
    }
    if(event->key() == Qt::Key_Left&&ui->redButton->isEnabled())
    {
        ui->redButton->setStyleSheet( QString("QPushButton{border:none;background-color:rgb(255, 119, 119);border-radius:75px;}"));
        on_redButton_clicked();
    }

    //Support for WASD
    if(event->key() == Qt::Key_A&&ui->redButton->isEnabled())
    {
        ui->redButton->setStyleSheet( QString("QPushButton{border:none;background-color:rgb(255, 119, 119);border-radius:75px;}"));
        on_redButton_clicked();
    }
    if(event->key() == Qt::Key_D&&ui->blueButton->isEnabled())
    {
        ui->blueButton->setStyleSheet( QString("QPushButton{border:none;background-color:rgb(119, 119, 255);border-radius:75px;}"));
        on_blueButton_clicked();
    }
}
void MainWindow::handler_reset_buttons_for_keys()
{
    ui->redButton->setStyleSheet( QString("QPushButton::!enabled {background-color: rgb(255,119,119);} QPushButton{border:none;background-color:rgb(119, 119, 119);border-radius:85px;} QPushButton:enabled{border:none; background-color:rgb(255, 0, 0); border-radius:85px;} QPushButton:pressed {border-radius:70px; background-color:rgb(119, 119, 119);}"));
    ui->blueButton->setStyleSheet( QString("QPushButton::!enabled {background-color: rgb(119,119,255);} QPushButton{border:none;background-color:rgb(119, 119, 119);border-radius:85px;} QPushButton:enabled{border:none; background-color:rgb(0, 0, 255); border-radius:85px;} QPushButton:pressed {border-radius:70px; background-color:rgb(119, 119, 119);}"));
}
