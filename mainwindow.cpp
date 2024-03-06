#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
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
    ui->blueButton->setEnabled(true);
    ui->redButton->setEnabled(true);
    ui->startButton->setEnabled(false);
}


void MainWindow::on_redButton_clicked()
{
    ui->testSeqLabel->setText(ui->testSeqLabel->text()+= '0');
}


void MainWindow::on_blueButton_clicked()
{
    ui->testSeqLabel->setText(ui->testSeqLabel->text()+= '1');
}

