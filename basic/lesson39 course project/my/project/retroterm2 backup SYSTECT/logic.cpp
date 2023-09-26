#include "logic.h"

logic::logic(QObject *parent)
    : QObject{parent}
{
    pConnection = new connection(this);
}


void logic::button_pressed(Buttons but)
{
    Q_UNUSED(but)
    if (but == Buttons::Disconnect)
        pConnection->disconnect_Adapter();
    else
    qDebug() << "Error. logic нет кнопки: " << __LINE__;
}

void logic::button_pressed(Buttons but, my_car car)
{
    if (but == Buttons::Connect) {
        pConnection->connect_Adapter(car);
        qDebug() << "logic: buton connect pressed";
    }
    else
        qDebug() << "Error. logic нет кнопки: " << __LINE__;
}

void logic::button_pressed(Buttons but, QString data)
{
    if (but == Buttons::Send)
        pConnection->send(data);
    else
        qDebug() << "Error. logic нет кнопки: " << __LINE__;
}
