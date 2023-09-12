#include "mainwindow.h"
#include <QClipboard>
#include <QDebug>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pLogic = new logic;
    pLogic->moveToThread(&logicThread);
    logicThread.start();

    connect(this,
            qOverload<Buttons>(&MainWindow::button_pressed),
            pLogic,
            qOverload<Buttons>(&logic::button_pressed));
    connect(this,
            qOverload<Buttons, QString>(&MainWindow::button_pressed),
            pLogic,
            qOverload<Buttons, QString>(&logic::button_pressed));

    connect(pLogic, &logic::recive, this, &MainWindow::recive_from_adapter);
    connect(pLogic, &logic::conection_stat, this, &MainWindow::conection_stat);
    init_gui();


}

void MainWindow::init_gui()
{
    ui->buttonDisconect->setEnabled(false);
    ui->buttonConect->setEnabled(false);
    ui->lblAdapter->setText("Адаптера нет");
    ui->lblAdapter->setStyleSheet(Grey); //highlighting[none]);
    ui->lblTCU->setText("БЭГ не отвечает");
    ui->lblTCU->setStyleSheet(Grey); //highlighting[none]);

    ui->comboSelectCar->addItems(car_struct::cars_all());

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

void MainWindow::on_buttonConect_clicked()
{
    ui->buttonConect->setEnabled(false);
    ui->comboSelectCar->setEnabled(false);
    ui->buttonDisconect->setEnabled(true);

    auto xx = ui->comboSelectCar->currentText();
    emit button_pressed(Buttons::Connect, xx);
}

void MainWindow::on_buttonDisconect_clicked()
{
    emit button_pressed(Buttons::Disconnect);
    ui->buttonConect->setEnabled(true);
}

void MainWindow::on_buttonTX_clicked()
{
    auto xx = ui->lineEditSend->text();
    emit button_pressed(Buttons::Send, xx);
}

void MainWindow::on_buttonStartLog_clicked()
{
    ui->buttonStopLog->setEnabled(true);
    ui->buttonStartLog->setEnabled(false);

    ui->cBox3Dfix->setEnabled(false);
    ui->cBoxCoordinates->setEnabled(false);
    ui->cBoxDTClist->setEnabled(false);
    ui->cBoxDTCpresence->setEnabled(false);
    ui->cBoxDistance->setEnabled(false);
    ui->cBoxTime->setEnabled(false);
}

#define bsl ui->buttonStartLog->setEnabled
void MainWindow::on_cBoxTime_clicked(bool checked)
{
    checked ? ++log_chosed : --log_chosed;
    log_chosed ? bsl(true) : bsl(false);
}
void MainWindow::on_cBox3Dfix_clicked(bool checked)
{
    checked ? ++log_chosed : --log_chosed;
    log_chosed ? bsl(true) : bsl(false);
}
void MainWindow::on_cBoxDTCpresence_clicked(bool checked)
{
    checked ? ++log_chosed : --log_chosed;
    log_chosed ? bsl(true) : bsl(false);
}

void MainWindow::on_cBoxCoordinates_clicked(bool checked)
{
    checked ? ++log_chosed : --log_chosed;
    log_chosed ? bsl(true) : bsl(false);
}

void MainWindow::on_cBoxDTClist_clicked(bool checked)
{
    checked ? ++log_chosed : --log_chosed;
    log_chosed ? bsl(true) : bsl(false);
}

void MainWindow::on_cBoxDistance_clicked(bool checked)
{
    checked ? ++log_chosed : --log_chosed;
    log_chosed ? bsl(true) : bsl(false);
}

void MainWindow::recive_from_adapter(QString data)
{
    ui->tBrowserRX->append(data);
}

void MainWindow::conection_stat(_connection_status stat)
{
    if (stat.Adapter == _connection_status::_Adapter::Connected) {
        ui->lblAdapter->setText("адаптер подключен");
        ui->lblAdapter->setStyleSheet(Green);
    }
    else if (stat.Adapter == _connection_status::_Adapter::Disconnected)
    {
        ui->lblAdapter->setText("адаптер отключен");
        ui->lblAdapter->setStyleSheet(Grey);
    }
    else if (stat.Adapter == _connection_status::_Adapter::Failed_to_connect)
    {
        ui->lblAdapter->setText("проверьте адаптер");
        ui->lblAdapter->setStyleSheet(Red);
    }
    else
        qDebug() << "ERROR mainwindow: " << __LINE__;

    if (stat.TCU == _connection_status::_TCU::Answering) {
        ui->lblTCU->setText("адаптер подключен");
        ui->lblTCU->setStyleSheet(Green);
    }
    else if (stat.TCU == _connection_status::_TCU::Not_answering)
    {
        ui->lblTCU->setText("адаптер отключен");
        ui->lblTCU->setStyleSheet(Grey);
    }
    else
        qDebug() << "ERROR mainwindow: " << __LINE__;
}

MainWindow::~MainWindow()
{
    logicThread.quit();
    logicThread.wait();
    pLogic->deleteLater();
    delete ui;
}






