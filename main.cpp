#include "mainwindow.h"
#include "model.h"
#include <QApplication>
/* Main for Simmon -Assign06 CS3505
 * @author Emma Eastland and Johnny Song
 * github users: eastland-emma and JohnnySongZ
 * https://github.com/UofU-CS3505/cs3505-assignment6-eastland-emma.git
 * Creative Element/Addition: support for arrow keys and WASD for the game.
 */
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
    QObject::connect(&receiver, &Model::reset_for_keys, &emitter, &MainWindow::handler_reset_buttons_for_keys);
    QObject::connect(&receiver, &Model::update_progress_signal, &emitter, &MainWindow::handler_update_progress);


    emitter.show();
    return a.exec();
}
