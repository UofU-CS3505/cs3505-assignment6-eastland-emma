#include "mainwindow.h"
#include "model.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow emitter;
    Model receiver;
    QObject::connect(&emitter, &MainWindow::on_redButton_clicked_signal, &receiver, &Model::handle_redButton_signal);
    QObject::connect(&emitter, &MainWindow::on_blueButton_clicked_signal, &receiver, &Model::handle_blueButton_signal);
    QObject::connect(&emitter, &MainWindow::on_startButton_clicked_signal, &receiver, &Model::handle_startButton_signal);
    QObject::connect(&emitter, &MainWindow::on_seqTestButton_clicked_signal, &receiver, &Model::handle_testseqButton_signal);
    QObject::connect(&receiver, &Model::turn_redLight_signal, &emitter, &MainWindow::handler_turn_red_Lights);
    QObject::connect(&receiver, &Model::turn_blueLight_signal, &emitter, &MainWindow::handler_turn_blue_Lights);
    QObject::connect(&receiver, &Model::playSequence_signal, &emitter, &MainWindow::playSequence);

    emitter.show();
    return a.exec();
}
