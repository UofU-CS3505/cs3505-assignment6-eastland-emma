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

    QObject::connect(&receiver, &Model::enable_buttons_signal, &emitter, &MainWindow::handler_enable_buttons);
    QObject::connect(&receiver, &Model::disable_buttons_signal, &emitter, &MainWindow::handler_disable_buttons);
    QObject::connect(&receiver, &Model::turn_redLight_signal, &emitter, &MainWindow::handler_turn_red_Lights);
    QObject::connect(&receiver, &Model::exitLights_signal, &emitter, &MainWindow::handler_exitLights);
    QObject::connect(&receiver, &Model::turn_blueLight_signal, &emitter, &MainWindow::handler_turn_blue_Lights);
    QObject::connect(&receiver, &Model::lose_screen_signal, &emitter, &MainWindow::handler_lose_Screen);
    QObject::connect(&receiver, &Model::turn_offLight_signal, &emitter, &MainWindow::handler_turn_off_Lights);


    emitter.show();
    return a.exec();
}
