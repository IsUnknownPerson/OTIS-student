#include "connection.h"

#include <QDebug>

connection::connection(QObject *parent)
    : QObject{parent}
{
    //pSystec = new Systect(this);
    pAdapter = new systec(this);

    connect(pAdapter, &systec::recived, this, &connection::ready_read);
    connect(pAdapter, &systec::systec_status, this, &connection::adapter_stat);
}



void connection::ready_read(uchar *d) //always 8 bytes
{
    for (size_t i = 0; i < 8; ++i)
        data[i] = d[i];

    emit recive(data);
}

void connection::connect_Adapter(QString carName)
{
    car = _car(carName);
    pAdapter->connect_Adapter(car);
}

void connection::adapter_stat(_connection_status::_Adapter stat)
{
    if (stat == _connection_status::_Adapter::Connected)
        qDebug() << "adapter connected";
    else if (stat == _connection_status::_Adapter::Disconnected)
        qDebug() << "adapter disconnected";
    else if (stat == _connection_status::_Adapter::Failed_to_connect)
        qDebug() << "ERROR connection adapter can't connect";
    else
        qDebug() << "ERROR connection: " << __LINE__;
    emit adapter_says(stat);
}

void connection::disconnect_Adapter()
{
    qDebug() << "closing systec";
    pAdapter->disconnect_Adapter();
}

void connection::send(uchar* data)
{
    pAdapter->send(data);
}



connection::~connection()
{

}
