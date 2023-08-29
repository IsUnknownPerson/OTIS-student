#include "systec.h"
#include <QDebug>

//https://marcmutz.wordpress.com/translated-articles/pimp-my-pimpl/

class systec::Private
{
public:
    // ... private data & methods ...
    void connect_Systec(my_car) const { qDebug() << "systec: connecting systec"; }

    void disconnect_Systec() const { qDebug() << "systec: connecting systec"; }

    void setup_Systec() const { qDebug() << "systec: connecting systec"; }

    QString getStatus_Systec() const
    {
        return "systecStatus";
        qDebug() << "systec: connecting systec";
    }

    void send_Systec(QString) const { qDebug() << "systec: connecting systec"; }

    void receive_Systec() const { qDebug() << "systec: connecting systec"; }
};

systec::systec()
    : impl(new Private)
{}

systec::~systec()
{
    delete impl;
}

//
//

void systec::connect_Adapter(my_car car)
{
    impl->connect_Systec(car);
}
void systec::disconnect_Adapter()
{
    impl->disconnect_Systec();
}
void systec::setup_Adapter()
{
    impl->setup_Systec();
}
QString systec::getStatus()
{
    return impl->getStatus_Systec();
}
void systec::send(QString data)
{
    impl->send_Systec(data);
}
void systec::receive()
{
    impl->receive_Systec();
}

