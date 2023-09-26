#include "greyBox.h"
#include <QDebug>
#include <QTimer>



greyBox::greyBox(QObject *parent)
    : QObject{parent}
{
    pCom_port_data = new QSerialPort(this);
    pCom_port_control = new QSerialPort(this);

    connect(pCom_port_data, &QSerialPort::readyRead,
            this, &greyBox::adapterRX);
    connect(pCom_port_data, &QSerialPort::errorOccurred,
            this, &greyBox::port_error_ocured);

    connect(pCom_port_control, &QSerialPort::readyRead,
            this, &greyBox::adapter_controlRX);
    connect(pCom_port_control, &QSerialPort::errorOccurred,
            this, &greyBox::port_control_error_ocured);
}


//    // XC886CLM    // 030407

void greyBox::adapter_controlRX(){
    //auto x = pCom_port_control->readAll();
}

void greyBox::adapterRX()
{    

    if (adapter_condition == Adapter_reset)
        ;
    else if (config_status == config_stages::config_done){
        auto x = pCom_port_data->readAll();
        emit adapter_say(Adapter_RX, x);
        //qDebug() << "Adapter get data: " << x;
    }
    else if (config_status == config_stages:: config_error)
        ;
    else {
        auto xx = pCom_port_data->readAll();
        configure_adapter(model, xx);
        //qDebug() << "config adapter. Recive: " << QString::number(xx[0], 16);
    }
}


void greyBox::connect_adapter()
{
   //if (pCom_port_data->isOpen())


    QString port1 = ""; QString port2 = "";
    QString com_port_to_open = "";
    QString com_port_control_to_open = "";

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        if ((info.manufacturer() == "FTDI") ||(info.productIdentifier() == 60000)
                || (info.productIdentifier() == 8963) /*синий переходник*/)

        {
            //            if (info.portName() > com_port_to_open)
            //                com_port_to_open = info.portName();
            if (port1 == "")
                port1 = info.portName();
            else
                port2 = info.portName();

        }
    }
    //if (com_port_to_open == "")
    if ((port1 == "") || (port2 == ""))
    {
        adapter_condition = No_adapter;
        emit adapter_say(adapter_condition, "");
        return;
    }

    if (port1 > port2){
        com_port_to_open = port1;
        com_port_control_to_open = port2;
    }
    else{
        com_port_to_open = port2;
        com_port_control_to_open = port1;
    }

    pCom_port_data->setPortName(com_port_to_open);
    pCom_port_control->setPortName(com_port_control_to_open);


    //    if (pCom_port_data->isOpen()) {
    //        adapter_condition = adapter_connected;
    //        config_status = config_stages::start;
    //    }
    /*else*/ if (pCom_port_data->open(QIODevice::ReadWrite))
    {
        pCom_port_data->setBaudRate(QSerialPort::Baud115200);
        pCom_port_data->setDataBits(QSerialPort::Data8);
        pCom_port_data->setParity(QSerialPort::NoParity);
        pCom_port_data->setStopBits(QSerialPort::OneStop);
        pCom_port_data->setFlowControl(QSerialPort::NoFlowControl);
        adapter_condition = adapter_connected;
        //config_status = config_stages::start;
    }
    else {
        adapter_condition = Adapter_port_bisy;
//        pCom_port_data.

                    pCom_port_data->close();
//                            pCom_port_data->clearError();
//                    pCom_port_data->reset();
    }

    if (adapter_condition == adapter_connected){
        if (pCom_port_control->open(QIODevice::ReadWrite))
        {
            pCom_port_control->setBaudRate(QSerialPort::Baud115200);
            pCom_port_control->setDataBits(QSerialPort::Data8);
            pCom_port_control->setParity(QSerialPort::NoParity);
            pCom_port_control->setStopBits(QSerialPort::OneStop);
            pCom_port_control->setFlowControl(QSerialPort::NoFlowControl);
            adapter_condition = adapter_connected;
            config_status = config_stages::start;
        }
        else {
            adapter_condition = Adapter_port_bisy;

\
//            pCom_port_control->close();
//                        pCom_port_control->clearError();
//            pCom_port_control->reset();
        }
    }

    emit adapter_say(adapter_condition, "");
}


void greyBox::configure_adapter(_adapter_settings::_Car_Model mod, QByteArray temp)
{
    if (mod == _adapter_settings::_Car_Model::model_unknown){
        qDebug() << "ERROR configure_adapter Car_Model::model_unknown";
        return;
    }
    auto data = (uchar*)temp.data();
    auto settings = adapter_settings.get_settings(mod);

    //adapter_condition = Adapter_is_configuring;
    //emit adapter_say(adapter_condition, "");

    switch (config_status)
    {
    //    case config_stages::wait:
    //        QTimer::singleShot(1000, this, [&, mod, temp]{
    //            config_status = config_stages::sended_XC886CLM;
    //            configure_adapter(mod, temp);
    //        });
    //        break;

    case config_stages::start:
        adapter_condition = Adapter_is_configuring;
        //qDebug() << "config_stages::start";
        model = mod;
        pCom_port_data->clear(QSerialPort::AllDirections);
        //pCom_port_data->readAll(); //очистка буфера
        pCom_port_data->write("XC886CLM");
        config_status = config_stages::sended_XC886CLM;
        break;

    case config_stages::sended_XC886CLM:
        //qDebug() << "config_stages::sended_XC886CLM. data: " << data[0];
        if (1/*data[0] == 0x02*/) {
            QString temp;
            switch (settings.mode) {
            case _adapter_settings::_Mode::Trunsparent:
                temp = "04000004"; break;
            case _adapter_settings::_Mode::Packet:
                pCom_port_data->write("04000105"); break;
            case _adapter_settings::_Mode::Monitoring_standard:
                pCom_port_data->write("04000206"); break;
            case _adapter_settings::_Mode::Monitoring_extended:
                pCom_port_data->write("04000307"); break;
            }

            pCom_port_data->write(QByteArray::fromHex(temp.toLatin1()));
            config_status = config_stages::sended_work_mode;
        }
        else
            config_status = config_stages::config_error;
        break;

    case config_stages::sended_work_mode:
        //qDebug() << "config_stages::sended_work_mode. data: " << data[0];
        if (1/*data[0] == 0x03*/) {
            //"090100000000079EAF", "09010100000007DEF0"
            QString temp;
            if (settings.CanIdRx.type == _adapter_settings::
                    _CanID::_Type_of_canID::standard) {
                temp = "090100000000" + settings.CanIdRx.value;
                temp += calculateCRC(temp);
            }
            else /*_Type_of_canID::extended*/{
                temp = "09010001" + settings.CanIdRx.value;
                temp += calculateCRC(temp);
            }
            pCom_port_data->write(QByteArray::fromHex(temp.toLatin1()));
            config_status = config_stages::sended_CanIdRx;
        }
        else
            config_status = config_stages::config_error;
        break;

    case config_stages::sended_CanIdRx:
        //qDebug() << "config_stages::sended_CanIdRx";
        if (1/*data[0] == 0x04*/) {
            //"090100000000079EAF", "09010100000007DEF0"
            QString temp;
            if (settings.CanIdRx.type == _adapter_settings::
                    _CanID::_Type_of_canID::standard) {
                temp = "090101000000" + settings.CanIdTx.value;
                temp += calculateCRC(temp);
            }
            else /*_Type_of_canID::extended*/{
                temp = "09010101" + settings.CanIdTx.value;
                temp += calculateCRC(temp);
            }
            pCom_port_data->write(QByteArray::fromHex(temp.toLatin1()));
            config_status = config_stages::sended_CanIdTx;
        }
        else
            config_status = config_stages::config_error;
        break;

    case config_stages::sended_CanIdTx:
        //qDebug() << "config_stages::sended_CanIdTx";
        if (1/*data[0] == 0x04*/) {
#define uspeed _adapter_settings::_UARTSpeed
            QString temp;
            if (settings.UARTSpeed == uspeed::_9_6_KBaud) temp = "040300";
            else if (settings.UARTSpeed == uspeed::_57_6_KBaud) temp = "040301";
            else if (settings.UARTSpeed == uspeed::_115_2_KBaud) temp = "040302";
            else if (settings.UARTSpeed == uspeed::_256_KBaud) temp = "040303";
            else if (settings.UARTSpeed == uspeed::_460_8_KBaud) temp = "040304";
            else if (settings.UARTSpeed == uspeed::_921_6_KBaud) temp = "040305";

            temp += calculateCRC(temp);

            pCom_port_data->write(QByteArray::fromHex(temp.toLatin1()));
            config_status = config_stages::sended_UARTSpeed;
        }
        else
            config_status = config_stages::config_error;
        break;

    case config_stages::sended_UARTSpeed:
        //qDebug() << "config_stages::sended_UARTSpeed";
        if (1/*data[0] == 0x06*/) {
#define cspeed _adapter_settings::_CanSpeed
            QString temp;
            if (settings.canSpeed == cspeed::_250_KBaud) temp = "04020006";
            else if (settings.canSpeed == cspeed::_500_KBaud) temp = "04020107";
            else if (settings.canSpeed == cspeed::_1_MBaud) temp = "04020208";
            pCom_port_data->write(QByteArray::fromHex(temp.toLatin1()));
            config_status = config_stages::sended_CANSpeed;
        }
        else
            config_status = config_stages::config_error;
        break;

    case config_stages::sended_CANSpeed:
        //qDebug() << "config_stages::sended_CANSpeed";
        if (1/*data[0] == 0x05*/){
            QString temp = "030407";
            pCom_port_data->write(QByteArray::fromHex(temp.toLatin1()));
            config_status = config_stages::sended_exit_sequence;
            //коробка глючит, не успевает послать ответ 01
            config_status = config_stages::config_done;
            adapter_condition = Adapter_configured;
        }
        else
            config_status = config_stages::config_error;
        break;

    case config_stages::sended_exit_sequence:
        //qDebug() << "config_stages::sended_exit_sequence";
        if (1/*data[0] == 0x01*/)
            config_status = config_stages::config_done;
        else
            config_status = config_stages::config_error;
        break;

    default:
        qDebug() << "ERROR config_stages::none";
        break;
    }

    if (config_status == config_stages::config_error) {
        adapter_condition = Adapter_error;
        config_status = config_stages::start;
    }
    else if (config_status == config_stages::config_done)
        adapter_condition = Adapter_configured;

    emit adapter_say(adapter_condition, "");

}

void greyBox::disconnect()
{
    adapter_condition = Adapter_port_disconnected;
    pCom_port_data->close();
    pCom_port_control->close();
    emit adapter_say(adapter_condition, "");
}

void greyBox::adapterTX(QByteArray data)
{    
    //qDebug() << "greyBox::adapterTX. data[0]: " << data[0];
    // -1: QIODevice::write (QSerialPort): device not open
    if (pCom_port_data->write(QByteArray::fromHex(data)) == -1){
disconnect();
    }
}


void greyBox::port_error_ocured(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::SerialPortError::NoError)
        adapter_condition = adapter_connected;
    else if (adapter_condition == Adapter_port_bisy){
        pCom_port_data->close();
    }
    else
        adapter_condition = No_adapter;

    emit adapter_say(adapter_condition, "");
}

void greyBox::port_control_error_ocured(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::SerialPortError::NoError)
        adapter_condition = adapter_connected;
    else if (adapter_condition == Adapter_port_bisy){
        pCom_port_control->close();
    }
    else
        adapter_condition = No_adapter;

    emit adapter_say(adapter_condition, "");
}

QString  greyBox::calculateCRC(QString data)
{
    int crc = 0; QString crc_str;

    for (int i=0; i<data.length(); i+=2)
    {
        QString temp = data[i]; temp += data[i+1];
        crc += temp.toInt(nullptr, 16);
    }

    crc_str = QString::number(crc, 16);
    if (crc_str.length() == 1)
        crc_str = "0" + crc_str;

    return crc_str;
}


void greyBox::reset_adapter(QString data)
{
    static int stage = 0;
    QByteArray buf;

    if ((adapter_condition != Adapter_configured) &&
        (adapter_condition != adapter_connected) &&
            (adapter_condition != Adapter_reset)){
            qDebug() << "ERROR greyBox::reset_adapter() adapter is disconected";
            adapter_condition = Adapter_reset;
            return;
    }
    else if ((data == "from gui") && (stage != 0)){
        qDebug() << "ERROR greyBox::reset_adapter() already resetting";
        return;
    }

    switch (stage) {
    case 0:
        ++stage; buf.clear();
        buf.append(0x82); buf.append(0x06); buf.append(0x06);
        pCom_port_control->write(buf);
        //QTimer::singleShot(30, this, &greyBox::reset_adapter);
        break;

    case 1:
        ++stage; buf.clear();
    //FT_SetBitMode(A, 0x00, 0x02) Спец команды драйвера ftdi

    default:
        break;
    }
    /*
    bool old_grey_box::reset()
    {
        speed_uart = Speed_Uart::speed_115200;
        BYTE buff[25] = {0};
        if ((FT_SetBaudRate(A, 115200)))
        {
            emit error_message("Ошибка настройки скорости A");
            return false;
        }
        if ((FT_SetBaudRate(B, 115200)))
        {
            emit error_message("Ошибка настройки скорости B");
            return false;
        }
        if ((FT_SetDataCharacteristics(A, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE)))
        {
            emit error_message("Ошибка настройки характеристик A");
            return false;
        }
        if ((FT_SetDataCharacteristics(B, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE)))
        {
            emit error_message("Ошибка настройки характеристик B");
            return false;
        }
        if (FT_SetBitMode(A, 0x00, 0x02) != FT_OK)
        {
            emit error_message("Ошибка применение маски A");
            return false;
        }
        Sleep(10);
        DWORD nb;
        buff[0] = 0x82; buff[1] = 0x06; buff[2] = 0x06;
        if (FT_Write(A, buff, 3, &nb) != FT_OK || nb != 3)
        {
            emit error_message("1 Ошибка записи в A");
            return false;
        }
        Sleep(30);
        buff[1] = 0x04;
        if (FT_Write(A, buff, 3, &nb) != FT_OK || nb != 3)
        {
            FT_SetBitMode(A, 0x00, 0x00);
            emit error_message("1 Ошибка записи в B");
            return false;
        }
        Sleep(100);
        buff[1] = 0x06;
        if (FT_Write(A, buff, 3, &nb) != FT_OK || nb != 3)
        {
            emit error_message("2 Ошибка записи в A");
            return false;
        }
        HANDLE hEvent;
        if (!(hEvent = CreateEvent(nullptr, false, false, nullptr)))
        {
            emit error_message("Ошибка создание события");
            return false;
        }
        if ((FT_SetEventNotification(B, FT_EVENT_RXCHAR, hEvent)))
        {
            CloseHandle(hEvent);
            emit error_message("Ошибка запуска события");
            return false;
        }
        while (WaitForSingleObject(hEvent, 100) != WAIT_TIMEOUT);
        CloseHandle(hEvent);
        if ((FT_GetQueueStatus(B, &nb))) // запрос количество байт
        {
            emit error_message("Ошибка запроса количества байт");
            return false;
        }
        PCHAR pBuf = nullptr;
        if (!(pBuf = static_cast<PCHAR>(malloc(nb + 1))))
        {
            emit error_message("Ошибка выделения памяти");
            return false;
        }
        Sleep(100);
        if ((FT_Read(B, pBuf, nb, &nb)))
        {
            emit error_message("Ошибка чтения результата");
            free(pBuf);
            return false;
        }
        pBuf[nb] = '\0';
        if (!strstr(pBuf, "\r\nXC886CLM reset\r\n"))
        {
            emit error_message("Не сошлись ответы при сбросе настроек");
            free(pBuf);
            return false;
        }
        free(pBuf);
        return true;
    }
*/
}










