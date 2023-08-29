#pragma once

#include "config.h"
#include "logic.h"

#include <QMainWindow>
#include <QThread>

#define Yellow "QLabel { background-color :yellow ; color : black; }"
#define Red "QLabel { background-color :red ; color : black; }"
#define GreenYellow "QLabel { background-color :greenyellow ; color : black; }"
#define Green "QLabel { background-color :green ; color : black; }"
#define Grey "QLabel { background-color: grey ; color : black; }"
#define White "QLabel { color : black; }"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void button_pressed(Buttons);
    void button_pressed(Buttons, my_car);

private slots:
    void on_comboSelectCar_currentIndexChanged(int index);
    void on_buttonConect_clicked();
    void on_buttonStartLog_clicked();
    void on_cBoxTime_clicked(bool checked);
    void on_cBox3Dfix_clicked(bool checked);
    void on_cBoxDTCpresence_clicked(bool checked);
    void on_cBoxCoordinates_clicked(bool checked);
    void on_cBoxDTClist_clicked(bool checked);
    void on_cBoxDistance_clicked(bool checked);

private:
    void init_gui();

    Ui::MainWindow *ui;

    QThread logicThread;
    logic *pLogic;

    int log_chosed = 0;
};
