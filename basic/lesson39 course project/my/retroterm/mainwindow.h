#pragma once

#include "definitions.h"
#include "logic.h"
#include <QMainWindow>
#include <QThread>
#include <QMap>

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

signals:
    void startTimer(int);
    void to_logic(from_gui, QString);

public slots:
    void from_logic(directives, int, QString);

private slots:
    void on_buttonDisconect_clicked();
    void on_buttonConect_clicked();
    void on_buttonStart_clicked();
    void on_buttonStop_clicked();

    void on_buttonICCID_clicked();

    void on_buttonSW_clicked();

    void on_buttonVehicle_SW_clicked();

    void on_buttonMidlet_SW_clicked();

    void on_buttonBoot_SW_clicked();

private:
        void init_gui();
        void copy_to_clipboard(QString);

private:
    Ui::MainWindow *ui;

    QThread logicThread;
    logic *pLogic;

    QClipboard *clipboard;
    //QClipboard *clipboard = QGuiApplication::clipboard();
    //clipboard->text();   //clipboard->setText(newText);

    QMap<int, QString> highlighting =
    {{TCU_online, Green},
     {TCU_offline, Red},
     {Adapter_configured, Green},
     {Adapter_is_configuring, GreenYellow},
     {Adapter_port_bisy, Yellow},
     {adapter_connect, Yellow},
     {No_adapter, Red},
     {Adapter_port_bisy, Red},
     {adapter_disconnect, Red},
     {adapter_disconected, Red},
     {Adapter_error, Red},
     {none,Grey}};

    QStringList Cars =
    {{"Марка авто"},
    {"Haval"},
    {"VAZ"},
    {"OMODA"}};

};
