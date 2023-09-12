#include "systec.h"
#include <QDebug>

//https://marcmutz.wordpress.com/translated-articles/pimp-my-pimpl/

class systec::Private
{
public:
    // ... private data & methods ...
    void connect_Systec(my_car) const { qDebug() << "systec: connecting systec"; }

    void disconnect_Systec() const { qDebug() << "systec: disconnecting systec"; }

    void setup_Systec() const { qDebug() << "systec: setup systec"; }

    QString getStatus_Systec() const
    {
        qDebug() << "systec: systec status: ";
        return "systecStatus: ";
    }

    void send_Systec(QString data) const { qDebug() << "systec: send systec: " << data; }

    void receive_Systec(QString data) const { qDebug() << "systec: receive systec: " << data; }
};

systec::systec()
    : impl(new Private)
{}

systec::~systec()
{
    delete impl;
}


void systec::connect_Adapter(my_car car)
{
    impl->connect_Systec(car);
}
void systec::disconnect_Adapter()
{
    impl->disconnect_Systec();
}
void systec::send(QString data)
{
    impl->send_Systec(data);
}
void systec::receive()
{
    impl->receive_Systec("QString");
}

