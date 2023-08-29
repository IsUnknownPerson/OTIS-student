#include "logic.h"

logic::logic(QObject *parent)
    : QObject{parent}
{
    pConnection = new connection;
}


void logic::button_pressed(Buttons but)
{
    Q_UNUSED(but)
    qDebug() << "Error. logic не реализовано: " << __LINE__;
}

void logic::button_pressed(Buttons but, my_car car)
{
    if (but == Buttons::Connect) {
        pConnection->connect_Adapter(car);
        qDebug() << "Buton Connect pressed";
    }
}
