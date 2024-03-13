#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow emitter;
    Model receiver;
    QObject::connect(&emitter, &MainWindow::on_redButton_clicked_signal, &receiver, &Model::handle_redButton_signal);
    QObject::connect(&emitter, &MainWindow::on_blueButton_clicked_signal, &receiver, &Model::handle_blueButton_signal);
    QObject::connect(&emitter, &MainWindow::on_startButton_clicked_signal, &receiver, &Model::handle_startButton_signal);
    emitter.show();
    return a.exec();
}
