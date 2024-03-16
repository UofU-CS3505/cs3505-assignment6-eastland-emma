#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
/* View and Controller Header for Simmon -Assign06 CS3505
 * @author Emma Eastland and Johnny Song
 */


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget *parent = nullptr);
    ~MainWindow();
    ///Turns on the red light on signal
    void handler_turn_red_Lights();
    ///Turns on the blue light on signal
    void handler_turn_blue_Lights();
    ///deactivates both lights on signal
    void handler_turn_off_Lights();
    ///Shows lose screen on signal
    void handler_lose_Screen();
    ///Reactivates the buttons for the user on signal
    void handler_exitLights();
    ///Activates the play buttons for the user on signal
    void handler_enable_buttons();
    ///Deactivates the play buttons for the user on signal
    void handler_disable_buttons();
    void handler_reset_buttons_for_keys();

signals:
    ///Notifies the model that the red button was pressed
    void on_redButton_clicked_signal();
    ///Notifies the model that the blue button was clicked
    void on_blueButton_clicked_signal();
    ///Notifies the model that the start button was clicked
    void on_startButton_clicked_signal();


private slots:
    ///sends signal for the red button to the model
    void on_redButton_clicked();
    ///sends signal for the blue button to the model
    void on_blueButton_clicked();
    ///sends signal for the start button to the model
    void on_startButton_clicked();


private:
    Ui::MainWindow *ui;

protected:
    ///@brief overrides key inputs and allows the user to use either AD or<> keys to select buttons
    void keyPressEvent(QKeyEvent *event) override;
};
#endif // MAINWINDOW_H
