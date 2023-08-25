#include "mainwindow.h"
#include <QClipboard>
#include <QDebug>
#include "config.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pLogic = new logic;
    pLogic->moveToThread(&logicThread);
    logicThread.start();

    init_gui();

    auto a = Haval::canSpeed;
    if (a == _CanSpeed::_500_KBaud)
        qDebug() << "500KBaud";
}

void MainWindow::init_gui()
{
    ui->buttonDisconect->setEnabled(false);
    ui->buttonConect->setEnabled(false);
    ui->lblAdapter->setText("Адаптера нет");
    ui->lblAdapter->setStyleSheet(Grey); //highlighting[none]);
    ui->lblTCU->setText("БЭГ не отвечает");
    ui->lblTCU->setStyleSheet(Grey); //highlighting[none]);

    ui->comboSelectCar->addItems(Cars);

    ui->buttonStopLog->setEnabled(false);
    ui->buttonStartLog->setEnabled(false);

    ui->buttonBoot_SW->setToolTip("copy");
    ui->buttonICCID->setToolTip("copy");
    ui->buttonMidlet_SW->setToolTip("copy");
    ui->buttonSW->setToolTip("copy");
    ui->buttonVehicle_SW->setToolTip("copy");
}


void MainWindow::on_comboSelectCar_currentIndexChanged(int index)
{
    if (index == 0)
        ui->buttonConect->setEnabled(false);
    else if (!ui->buttonDisconect->isEnabled())
        ui->buttonConect->setEnabled(true);
}

MainWindow::~MainWindow()
{
    logicThread.quit();
    logicThread.wait();
    pLogic->deleteLater();
    delete ui;
}
