#include "systec.h"
#include <QDebug>

systec::systec(QObject *parent)
    : QObject{parent}
{
    pSystec = new Systect(this);

    connect(pSystec, &Systect::StatusInitialize, this, &systec::systect_init_status);
    connect(pSystec, &Systect::disconnection, this, &systec::systect_close_status);
    connect(pSystec, &Systect::readyRead, this, &systec::ready_read);
}

void systec::connect_Adapter(car_struct car)
{
    //standart or extended, CanId TX                     CanID RX
    //can_id =         {{0, 0x00, 0x00, 0x07, 0xca}, {0, 0x00, 0x00, 0x00, 0x56}};

    //test--->


    //<--test



    int canID;
    QVector<int> RX = from_string_to_hex(car.CanIdRx);
    QVector<int> TX = from_string_to_hex(car.CanIdTx);
    (car.canID == _Type_of_canID::standard) ? canID = 0 : canID = 1;

    QVector<save_array> can_id = {{canID, TX[0], TX[1], TX[2], TX[3]},
                                  {canID, RX[0], RX[1], RX[2], RX[3]}};//0x00, 0x56}};

    pSystec->SetCanId(can_id);
    pSystec->setSpeedCan(Speed_Can::speed_500_KBaud);

    pSystec->initialize();
}

void systec::ready_read()
{
    save_array xx = pSystec->readALL();
    if (xx.size() < 8) {
        qDebug() << "ERROR systec rx size < 8";
        return;
    }
    auto zz = xx.u_data();
    emit recived(zz);
}
void systec::disconnect_Adapter()
{
    pSystec->close();
}

void systec::send(uchar *data) //always 8 bytes
{
    save_array xx = {data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]};
    pSystec->write(xx);
}

void systec::systect_init_status(bool stat)
{
    if (stat)
        emit systec_status(_connection_status::_Adapter::Connected);
    else
        emit systec_status(_connection_status::_Adapter::Failed_to_connect);
}
void systec::systect_close_status()
{
    emit systec_status(_connection_status::_Adapter::Disconnected);
}

QVector<int> systec::from_string_to_hex(QString car)
{
    bool success = false;
    QVector<int> X = {0, 0, 0, 0};
    auto n = car.length() % 2 + car.length() / 2 - 1;
    QString temp = car[0];
    int i = 0;
    if (car.length() % 2)
        ++i;
    else {
        temp += car[1];
        i += 2;
    }
    X[3 - n] = temp.toInt(&success, 16);
    if (!success)
        qDebug() << "ERROR systec: " << __LINE__;

    for (; i <= (2 * n); i += 2) {
        temp = car[i];
        temp += car[i + 1];
        X[3 - n + i / 2 + car.length() % 2] = temp.toInt(&success, 16);
        if (!success)
            qDebug() << "ERROR systec: " << __LINE__;
    }
    return X;
}

systec::~systec() {}
