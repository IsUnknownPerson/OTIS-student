#pragma once

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
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_comboSelectCar_currentIndexChanged(int index);

private:
    void init_gui();

    Ui::MainWindow *ui;

    QThread logicThread;
    logic *pLogic;

    QStringList Cars =
        {{"Марка авто"},
         {"Haval"},
         {"VAZ"},
         {"OMODA"}};
};
