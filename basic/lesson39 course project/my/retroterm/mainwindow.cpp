#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QClipboard>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pLogic = new logic;

    connect(pLogic, &logic::to_mainwindow,
            this, &MainWindow::from_logic);

    pLogic->moveToThread(&logicThread);
    connect(this, &MainWindow::startTimer,
            pLogic, &logic::startTimer);

    connect(&logicThread, &QThread::started, this, [&]()
    {//на всякий случай отсюда стартую таймер, а то вдруг
        emit startTimer(1000);//создастся вместе с логикой
    });// в старом потоке, и в новый перейдет только логика
    logicThread.start();

    connect(this, &MainWindow::to_logic, pLogic, &logic::from_mainwindow);

    init_gui();
}


void MainWindow::from_logic(directives dir, int inter, QString data)
{
    /*
    auto ascii = (uchar *) data.data();
    for (size_t i = 0; i < data.size(); ++i) {
        if ((ascii[i] < 0x20) || (ascii[i] > 0x7E)) {
            qDebug() << "MainWindow::from_logic ascii ERROR: " << data[i];
            return;
        }
    }
*/

    switch (dir) {
    case directives::Connection:
        if ((inter == No_adapter) || (inter == Adapter_port_bisy) ||
                (inter == adapter_disconnect) || (inter == adapter_disconected) ||
                (inter == Adapter_error) || (inter == none)){
            ui->lblAdapter->setText("Адаптера нет");
            ui->lblAdapter->setStyleSheet(highlighting[inter]);
            ui->lblTCU->setText("БЭГ не отвечает");
            ui->lblTCU->setStyleSheet(highlighting[inter]);
        }
        else if (inter == TCU_online){
            ui->lblTCU->setText("БЭГ соединен");
            ui->lblTCU->setStyleSheet(highlighting[inter]);
        }
        else if (inter == TCU_offline){
            ui->lblTCU->setText("БЭГ не отвечает");
            ui->lblTCU->setStyleSheet(highlighting[inter]);
        }
        else if (inter == Adapter_configured){
            ui->lblAdapter->setText("Адаптер подключен");
            ui->lblAdapter->setStyleSheet(highlighting[inter]);
        }

        else
            ui->lblAdapter->setStyleSheet(highlighting[inter]);
        break;

    case directives::DTC:
        ui->tBrowserDTC->clear();
        for (auto &text : data.split("___"))
            ui->tBrowserDTC->append(text);
        break;

    case directives::GNSS_realibility:
        ui->lblReliability->setText(data);
        if (data == "NOT reliable")
            ui->lblReliability->setStyleSheet("QLabel { color : red; }");
        else if (data == "reliable")
            ui->lblReliability->setStyleSheet("QLabel { color : black; }");
        break;

    case directives::GNSS_coordinates:
    {
        auto temp = data.split("___");
        if (temp.size() < 3)
            break;
        ui->lblLatitude->setText(temp[0]);
        ui->lblLongitude->setText(temp[1]);
        ui->lblDistanse->setText(temp[2]);
        auto temp2 = temp[2].split(" ");

        if (temp2[1].toDouble() >= 15)
            ui->lblDistanse->setStyleSheet("QLabel { color : red; }");
        else
            ui->lblDistanse->setStyleSheet("QLabel { color : black; }");
    }
        break;

    case directives::ICCIDG:
    {
        auto ascii = (uchar *) data.data();
        for (size_t i = 0; i < data.size(); ++i) {
            if ((ascii[i] < 0x20) || (ascii[i] > 0x7E)) {
                qDebug() << "MainWindow::from_logic ascii ERROR: " << data[i];
                return;
            }
        }



        auto temp = data.split("_");
        if(temp.size() == 2)
            ui->lblICCID->setText("ICCID: " + temp[1]);
        else
            ui->lblICCID->setText("ICCID: ERROR");
    }
        break;

    case directives::SW_Version:
        ui->lblSW->setText("SW: " + data);
        break;

    case directives::Vehicle_SW_Version:
        ui->lblVehicle_SW->setText("Vehicle_SW: " + data);
        break;

    case directives::Midlet_SW_Version:
        ui->lblMidlet_SW->setText("Midlet_SW: " + data);
        break;

    case directives::Boot_SW_Version:
        ui->lblBoot_SW->setText("Boot_SW: " + data);
        break;

    default:
        qDebug() << "MainWindow::from_logic Unknown directives";
        break;
    }
}



void MainWindow::init_gui()
{
    ui->buttonDisconect->setEnabled(false);
    ui->lblAdapter->setText("Адаптера нет");
    ui->lblAdapter->setStyleSheet(highlighting[none]);
    ui->lblTCU->setText("БЭГ не отвечает");
    ui->lblTCU->setStyleSheet(highlighting[none]);

    ui->comboSelectCar->addItems(Cars);
    ui->buttonStop->setEnabled(false);

    ui->buttonBoot_SW->setToolTip("copy");
    ui->buttonICCID->setToolTip("copy");
    ui->buttonMidlet_SW->setToolTip("copy");
    ui->buttonSW->setToolTip("copy");
    ui->buttonVehicle_SW->setToolTip("copy");
}


void MainWindow::on_buttonDisconect_clicked()
{
    //emit to_logic(from_gui::buttonDisconect, "");
}


void MainWindow::on_buttonConect_clicked()
{
    auto temp = ui->comboSelectCar->currentText();

    if (temp == ui->comboSelectCar->itemText(0))
        return;
    else{
        ui->buttonConect->setEnabled(false);
        ui->comboSelectCar->setEnabled(false);
        emit to_logic(from_gui::buttonConect, temp);
    }
}


void MainWindow::on_buttonStart_clicked()
{
    QString temp = "";

    if (ui->cBoxTime->checkState())
        temp += "Time;";
    if (ui->cBoxDTCpresence->checkState())
        temp += "DTC_quantity;";
    if (ui->cBoxDTClist->checkState())
        temp += "DTC_list;";
    if (ui->cBox3Dfix->checkState())
        temp += "Coords_reliability;";
    if (ui->cBoxCoordinates->checkState())
        temp += "Gnss_coordinates;";
    if (ui->cBoxDistance->checkState())
        temp += "Distance;";

    if (temp == "")
        return;

    ui->buttonStop->setEnabled(true);
    ui->buttonStart->setEnabled(false);
    ui->cBox3Dfix->setEnabled(false);
    ui->cBoxCoordinates->setEnabled(false);
    ui->cBoxDTClist->setEnabled(false);
    ui->cBoxDTCpresence->setEnabled(false);
    ui->cBoxDistance->setEnabled(false);
    ui->cBoxTime->setEnabled(false);

    emit to_logic(from_gui::buttonStart_Log, temp);
}

void MainWindow::on_buttonStop_clicked()
{
    ui->buttonStop->setEnabled(false);
    ui->buttonStart->setEnabled(true);
    ui->cBox3Dfix->setEnabled(true);
    ui->cBoxCoordinates->setEnabled(true);
    ui->cBoxDTClist->setEnabled(true);
    ui->cBoxDTCpresence->setEnabled(true);
    ui->cBoxDistance->setEnabled(true);
    ui->cBoxTime->setEnabled(true);

    emit to_logic(from_gui::buttonStop_Log, "");
}


MainWindow::~MainWindow()
{
    logicThread.quit();
    logicThread.wait();
    pLogic->deleteLater();

    delete ui;
}

void MainWindow::on_buttonICCID_clicked(){
    copy_to_clipboard(ui->lblICCID->text());
}
void MainWindow::on_buttonSW_clicked(){
    copy_to_clipboard(ui->lblSW->text());
}
void MainWindow::on_buttonVehicle_SW_clicked(){
    copy_to_clipboard(ui->lblVehicle_SW->text());
}
void MainWindow::on_buttonMidlet_SW_clicked(){
    copy_to_clipboard(ui->lblMidlet_SW->text());
}
void MainWindow::on_buttonBoot_SW_clicked(){
    copy_to_clipboard(ui->lblBoot_SW->text());
}

void MainWindow::copy_to_clipboard(QString data){
    auto temp = data.split(": ");
    if (temp.size() > 1)
    clipboard->setText(temp[1]);
}

