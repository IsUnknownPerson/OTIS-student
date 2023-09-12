#include "connection.h"
#include <QTime>

#include <QDebug>

connection::connection(QObject *parent)
    : QObject{parent}
{
    pSystec = new Systect(this);

    connect(pSystec, &Systect::StatusInitialize, this, &connection::systect_init_stat);
    connect(pSystec, &Systect::disconnection, this, &connection::systect_close_stat);
    connect(pSystec, &Systect::readyRead, this, &connection::ready_read);
}



void connection::ready_read()
{
    auto xx = pSystec->readALL();

        QString full_date = QTime::currentTime().toString("mm_ss_zzz");
    qDebug() << full_date << " ready read: " << xx.byte_in_string();
}

void connection::connect_Adapter(my_car car)
{
    //0, 0x00, 0x00, 0x07, 0xca
    //standart or extended, CANId   //TX                            //RX
    QVector<save_array> can_id = {{0, 0x00, 0x00, 0x07, 0xca}, {0, 0x00, 0x00, 0x00, 0x56}};
    pSystec->SetCanId(can_id);

    Speed_Can speed = Speed_Can::speed_500_KBaud;
    pSystec->setSpeedCan(speed);

    pSystec->initialize();
}

void connection::systect_init_stat(bool stat)
{
    if (stat)
        qDebug() << "systec connected";
    else
        qDebug() << "ERROR connection systec can't connect";
}

void connection::systect_close_stat()
{
    qDebug() << "Systec closed";
}

void connection::disconnect_Adapter()
{
    qDebug() << "closing systec";
    //    pSystec->disconnect_Adapter();
    pSystec->close();
}

void connection::send(QString data)
{
    qDebug() << "trying to send: " << data;

    pSystec->write(data.toUtf8()); //ut8
    //pSystec->WriteWithID(data.toUtf8(), x);
}
void connection::receive(QString data)
{
   qDebug() <<"reciving: " << data;
}


connection::~connection()
{

}
