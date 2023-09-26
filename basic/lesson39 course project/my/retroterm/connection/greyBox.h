#pragma once

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QVector>
#include "definitions.h"
#include "connection/settings.h"




class greyBox : public QObject
{
    Q_OBJECT
public:
    explicit greyBox(QObject *parent = nullptr);

    enum class config_stages : int {
        wait,
        start,
        sended_XC886CLM,
        sended_work_mode,
        sended_CanIdRx,
        sended_CanIdTx,
        sended_UARTSpeed,
        sended_CANSpeed,
        sended_exit_sequence,


        config_done,
        config_error
 };


    void connect_adapter();
    void configure_adapter(_adapter_settings::_Car_Model, QByteArray);
    void reset_adapter(QString);
    void disconnect();


signals:
    void adapter_say(int, QByteArray);


public slots:
    void port_error_ocured(QSerialPort::SerialPortError);
    void port_control_error_ocured(QSerialPort::SerialPortError);
    void adapterRX();
    void adapter_controlRX();
    void adapterTX(QByteArray);

private:
    QString calculateCRC(QString);


private:
    QSerialPort *pCom_port_data;
    QSerialPort *pCom_port_control;

    _car_CAN_settings adapter_settings;
    _adapter_settings::_Car_Model model =
            _adapter_settings::_Car_Model::model_unknown;
    int adapter_condition = No_adapter;
    config_stages config_status = config_stages::start;
};
